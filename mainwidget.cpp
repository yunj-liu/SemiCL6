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

#include "SemiCL6Func.h"
#include <QMessageBox>

MainWidget::MainWidget(QWidget *parent)
    : QWidget(parent)
    , m_listView(new QListView(this))
    , m_listModel(new QStringListModel(this))
    , m_contentArea(new QWidget(this))
    , m_datatableMap(generateFigureData())
{
    m_exampleMap.insert(tr("Chart Themes"), ChartThemes);
    m_exampleMap.insert(tr("F1_Find lowest nmodes eigenvectors and eigenvalues of sparse matrix"), F1_LineChart);  //tr return type is QString
    m_exampleMap.insert(tr("F2_Energy dispersion of conduction"), F2_LineChart);
    m_exampleMap.insert(tr("F3_Structure of valence band"), F3_LineChart);
    m_exampleMap.insert(tr("F4_Material gain"), F4_LineChart);
    m_exampleMap.insert(tr("F5_DBR Reflectivity"), F5_LineChart);
    m_exampleMap.insert(tr("F6_VECSEL standing wave field and electric field distribution"), F6_LineChart);
    m_exampleMap.insert(tr("F7_VECSEL longitudinal confinement factor"), F7_LineChart);

    QStringList examples = m_exampleMap.keys();  //QStringList is QList<QString>, m_exampleMap type is QHash<QString, Example>
    std::sort(examples.begin(), examples.end());  // according to string sort
    m_listModel->setStringList(examples);  //Sets the model's internal string list to strings. The model will notify any attached views that its underlying data has changed.

    m_listView->setMaximumWidth(220);  //the QListView in left of window, width is 220
    m_listView->setModel(m_listModel); //set the model for the view to present. model & it's attached view
    m_listView->setCurrentIndex(m_listModel->index(0));  //the param's type is QModelIndex
    m_listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    setMinimumSize(800, 400);  // MainWidget's minimum width and height
    resize(1200, 600);  // the MainWidget's init width and height in program startup

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

    qApp->setApplicationDisplayName(tr("SemiCL - NCAMCQ"));
    qApp->setWindowIcon(QIcon(":/main.ico"));  //icon in topleft of main window. the icon file in the qrc

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

FigureData MainWidget::generateFigureData() const{
    FigureData datatableMap;
    if (!SemiCL6FuncInitialize()) // DLL Initialize
    {
        QMessageBox msgBox;
        msgBox.setText("SemiCL DLL initialization failed.");
        msgBox.exec();
    }
    //figure1 array
    mwArray matrix_f1_x(1, 1120, mxDOUBLE_CLASS, mxREAL);    //first 2 param indicate rowCnt, colCnt. 1 row,1120 cols, store in col priority , also means 1 col, 1120 rows.
    mwArray matrix_f1_ph1(1, 1120, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f1_ph2(1, 1120, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f1_ph3(1, 1120, mxDOUBLE_CLASS, mxREAL);
    //figure2 array
    mwArray matrix_f2_x(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f2_E1(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f2_E2(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f2_E3(1, 81, mxDOUBLE_CLASS, mxREAL);
    //figure3 array
    mwArray matrix_f3_x(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f3_HH1(1, 81, mxDOUBLE_CLASS, mxREAL);  //in matlab the array is 81*1, but use 1*81 there can still read the data
    mwArray matrix_f3_HH2(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f3_HH3(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f3_LH1(1, 81, mxDOUBLE_CLASS, mxREAL);
    //figure4 array
    mwArray matrix_f4_x(1, 301, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f4_gai(1, 301, mxDOUBLE_CLASS, mxREAL);
    //figure5 array
    mwArray matrix_f5_x(1, 301, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f5_ref(1, 301, mxDOUBLE_CLASS, mxREAL);
    //figure6 array
    mwArray matrix_f6_x(1, 9252, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f6_YYy(1, 9252, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f6_mm1(1, 1, mxDOUBLE_CLASS, mxREAL);
    //figure7 array
    mwArray matrix_f7_x(1, 301, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f7_TT(1, 301, mxDOUBLE_CLASS, mxREAL);





    int nargout=22;  // the number of return params. must correct.
    SemiCL6Func(nargout,
                matrix_f1_x, matrix_f1_ph1, matrix_f1_ph2, matrix_f1_ph3,
                matrix_f2_x, matrix_f2_E1, matrix_f2_E2, matrix_f2_E3,
                matrix_f3_x, matrix_f3_HH1, matrix_f3_HH2, matrix_f3_HH3, matrix_f3_LH1,
                matrix_f4_x, matrix_f4_gai,
                matrix_f5_x, matrix_f5_ref,
                matrix_f6_x, matrix_f6_YYy, matrix_f6_mm1,
                matrix_f7_x, matrix_f7_TT
                );

    int listCount(0);
    int valueCount(0);

    //figure 1
    listCount = 3;
    valueCount = 1120;
    mwArray* f1_ph[3];
    f1_ph[0] = &matrix_f1_ph1;
    f1_ph[1] = &matrix_f1_ph2;
    f1_ph[2] = &matrix_f1_ph3;
    DataTable datatable_figure1;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f1_x.Get(1, j+1), f1_ph[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure1 << dataList;
    }
    datatableMap.insert(tr("figure1"), datatable_figure1);

    //figure 2
    mwArray* f2_E[3];
    f2_E[0] = &matrix_f2_E1;
    f2_E[1] = &matrix_f2_E2;
    f2_E[2] = &matrix_f2_E3;
    listCount = 3;
    valueCount = 81;
    DataTable datatable_figure2;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f2_x.Get(1, j+1), f2_E[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure2 << dataList;
    }
    datatableMap.insert(tr("figure2"), datatable_figure2);

    //figure 3
    mwArray* f3_p[4];
    f3_p[0] = &matrix_f3_HH1;
    f3_p[1] = &matrix_f3_HH2;
    f3_p[2] = &matrix_f3_HH3;
    f3_p[3] = &matrix_f3_LH1;
    listCount = 4;
    valueCount = 81;
    DataTable datatable_figure3;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f3_x.Get(1, j+1), f3_p[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure3 << dataList;
        //qDebug() << "list:";
        //qDebug() << dataList;
    }
    datatableMap.insert(tr("figure3"), datatable_figure3);

    //figure 4
    mwArray* f4_p[1];
    f4_p[0] = &matrix_f4_gai;
    listCount = 1;
    valueCount = 301;
    DataTable datatable_figure4;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f4_x.Get(1, j+1), f4_p[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure4 << dataList;
        //qDebug() << "list:";
        //qDebug() << dataList;
    }
    datatableMap.insert(tr("figure4"), datatable_figure4);

    //figure 5
    mwArray* f5_p[1];
    f5_p[0] = &matrix_f5_ref;
    listCount = 1;
    valueCount = 301;
    DataTable datatable_figure5;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f5_x.Get(1, j+1), f5_p[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure5 << dataList;
        //qDebug() << "list:";
        //qDebug() << dataList;
    }
    datatableMap.insert(tr("figure5"), datatable_figure5);

    //figure 6
    mwArray* f6_p[2];
    f6_p[0] = &matrix_f6_YYy;
    f6_p[1] = &matrix_f6_mm1;  //pass by a single number
    listCount = 2;
    valueCount = 9252;
    DataTable datatable_figure6;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        if(i < listCount-1){
            for (int j(0); j < valueCount; j++) {
                QPointF value(matrix_f6_x.Get(1, j+1), f6_p[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
                QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
                dataList << Data(value, label);
            }
        }
        else
        {
            //last datalist store a single number: matrix_f6_mm1
            for (int j(0); j < 1; j++) {  //j<1, indicate a single number
                QPointF value(0, f6_p[i]->Get(1, j+1)); //first param is not use. value.x() and value .y() can get two values
                QString label = "Slice " + QString::number(i) + ":" + "matrix_f6_mm1";
                dataList << Data(value, label);
            }
        }
        datatable_figure6 << dataList;
    }
    datatableMap.insert(tr("figure6"), datatable_figure6);

    //figure7
    mwArray* f7_p[1];
    f7_p[0] = &matrix_f7_TT;
    listCount = 1;
    valueCount = 301;
    DataTable datatable_figure7;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f7_x.Get(1, j+1), f7_p[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure7 << dataList;
    }
    datatableMap.insert(tr("figure7"), datatable_figure7);

    return datatableMap;
}

MainWidget::~MainWidget()
{
}

