/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:39.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#include "mainwidget.h"
#include "f1_linewidget.h"
#include "f2_linewidget.h"
#include "f3_linewidget.h"
#include "f4_linewidget.h"
#include "f5_linewidget.h"
#include "f6_linewidget.h"
#include "f7_linewidget.h"
#include "themewidget.h"

#include <QApplication>  //qApp need this include
#include <QHBoxLayout>

//#include "SemiCL6Func.h"
//#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , m_listView(new QListView(this))
    , m_listModel(new QStringListModel(this))
    , m_contentArea(new QWidget(this))
    //, m_datatableMap(CommonControl::generateFigureData())
    , m_datatableMap(CommonControl::getFigureDataHashMapFromCsvFile("/projdata/", 7))
{
    m_exampleMap.insert(tr("Fig.0 总览图"), ChartThemes);
    m_exampleMap.insert(tr("Fig.1 导带电子波函数"), F1_LineChart);  //tr return type is QString
    m_exampleMap.insert(tr("Fig.2 导带电子能量色散关系"), F2_LineChart);
    m_exampleMap.insert(tr("Fig.3 价带空穴能量色散关系"), F3_LineChart);
    m_exampleMap.insert(tr("Fig.4 量子阱材料增益谱"), F4_LineChart);
    m_exampleMap.insert(tr("Fig.5 DBR反射谱"), F5_LineChart);
    m_exampleMap.insert(tr("Fig.6 增益芯片内部驻波场电场分布"), F6_LineChart);
    m_exampleMap.insert(tr("Fig.7 增益芯片纵模限制因子"), F7_LineChart);

    examples = m_exampleMap.keys();  //QStringList is QList<QString>, m_exampleMap type is QHash<QString, Example>
    std::sort(examples.begin(), examples.end());  // according to string sort
    m_listModel->setStringList(examples);  //Sets the model's internal string list to strings. The model will notify any attached views that its underlying data has changed.

    m_listView->setMaximumWidth(220);  //the QListView in left of window, width is 220
    m_listView->setModel(m_listModel); //set the model for the view to present. model & it's attached view
    m_listView->setCurrentIndex(m_listModel->index(0));  //the param's type is QModelIndex
    m_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    setMinimumSize(800, 400);  // MainWidget's minimum width and height
    //resize(1200, 600);  // the MainWidget's init width and height in program startup
    resize(1800, 900);

    auto layout = new QHBoxLayout(this);
    layout->addWidget(m_listView);  //QHBoxLayout, horizontal. m_listView is QListView.
    layout->addWidget(m_contentArea);  // two part, left and right in horizon. m_contentArea is QWidget
    setLayout(layout); //MainWidget->layout: include m_listView(QListView) & m_contentArea(QWidget)

    /*
    connect proto:
    template<typename PointerToMemberFunction>
    static QMetaObject::Connection connect(const QObject *sender, PointerToMemberFunction signal, const QObject *receiver, PointerToMemberFunction method, Qt::ConnectionType type = Qt::AutoConnection);

    template<typename PointerToMemberFunction, typename Functor>
    static QMetaObject::Connection connect(const QObject *sender, PointerToMemberFunction signal, Functor functor);

    template<typename PointerToMemberFunction, typename Functor>
    static QMetaObject::Connection connect(const QObject *sender, PointerToMemberFunction signal, const QObject *context, Functor functor, Qt::ConnectionType type = Qt::AutoConnection);

    The purpose of this function is to associate the signal in the sender object with the member slot function in the receiver.
    The parameters of the signal function are passed directly to the slot function.
    The number of parameters of the signal function must be greater than the number of parameters of the slot function,
    and the parameters of the signal function are passed in order

    m_listView->selectionModel() type is QItemSelectionModel *
    the signal function currentChanged has two parameters: void currentChanged(const QModelIndex &current, const QModelIndex &previous);
    the 2nd parameter of function connect is pointer, so use reference &QItemSelectionModel::currentChanged

    Lambda function :
    [capture](parameters)->return-type{body}
    [capture](parameters){body}
    [this](const QModelIndex &index) is Lambda function, it's slot function, has one parameter. it will receive signal function's first parameter.
    [this] —— means capture this pointer, you can use this->setActiveExample, this->m_exampleMap, this->m_listModel, the below is omit this->
    */
    connect(m_listView->selectionModel(), &QItemSelectionModel::currentChanged, this,
            [this](const QModelIndex &index) {
                setActiveExample(m_exampleMap[m_listModel->data(index).toString()]);  //data is QVariant type, m_listModel is QStringListModel
            }); //param of setActiveExample is Example

    setActiveExample(m_exampleMap[examples[0]]);  //examples is QStringList, m_exampleMap is QHash<QString, Example>

    setMouseTracking(true);

    //qApp->setApplicationDisplayName(tr("SemiCL - NCAMCQ"));
    //qApp->setWindowIcon(QIcon(":/main.ico"));  //icon in topleft of main window. the icon file in the qrc

}

void MainWidget::resizeEvent(QResizeEvent *)
{
    m_activeWidget->resize(m_contentArea->size());
}

void MainWidget::setActiveExample(Example example) //constructor call once, and being slot function waiting for CurrentChanged signal
{
    // We only keep one example alive at the time to save resources.
    // This also allows resetting the example by switching to another example and back.
    if (m_activeWidget) {
        m_activeWidget->setVisible(false);
        m_activeWidget->deleteLater();
    }

    switch (example) {
    case ChartThemes:
        m_activeWidget = new ThemeWidget(m_contentArea, &m_datatableMap);
        break;
    case F1_LineChart:  //m_contentArea is QWidget, being the parent passing to the LineWidget
        m_activeWidget = new F1_LineWidget(m_contentArea, &m_datatableMap[tr("figure1")]);  //m_activeWidget is ContentWidget, LineWidget derived from ContentWidget
        break;               //parent: m_contentArea(QWidget)->m_contentArea(ConetentWidget)->m_activeWidget(LineWidget)
    case F2_LineChart:
        m_activeWidget = new F2_LineWidget(m_contentArea, &m_datatableMap[tr("figure2")]);
        break;
    case F3_LineChart:
        m_activeWidget = new F3_LineWidget(m_contentArea, &m_datatableMap[tr("figure3")]);
        break;
    case F4_LineChart:
        m_activeWidget = new F4_LineWidget(m_contentArea, &m_datatableMap[tr("figure4")]);
        break;
    case F5_LineChart:
        m_activeWidget = new F5_LineWidget(m_contentArea, &m_datatableMap[tr("figure5")]);
        break;
    case F6_LineChart:
        m_activeWidget = new F6_LineWidget(m_contentArea, &m_datatableMap[tr("figure6")]);
        break;
    case F7_LineChart:
        m_activeWidget = new F7_LineWidget(m_contentArea, &m_datatableMap[tr("figure7")]);
        break;
    }

    m_activeWidget->load();
    m_activeWidget->resize(m_contentArea->size());
    m_activeWidget->setVisible(true);
}

void MainWidget::doMatlabDone(const QString info, const FigureData figure_datatablemap)
{
    m_datatableMap = figure_datatablemap;
    setActiveExample(m_exampleMap[examples[0]]);
    setMouseTracking(true);
}


MainWidget::~MainWidget()
{
}

