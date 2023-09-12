/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:39.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#include "themewidget.h"
#include "ui_themewidget.h"  //name 'themewidget' is the *.ui name

#include <QRandomGenerator>
#include <QLineSeries>
#include <QValueAxis>
#include <QSplineSeries>

ThemeWidget::ThemeWidget(QWidget *parent, FigureData *figure_datatablemap):
    ContentWidget(parent),  //contentwidget.h have been included in themewidget.h
    m_listCount(3),
    m_valueMax(10),
    m_valueCount(7),
    //m_dataTable(generateRandomData(m_listCount, m_valueMax, m_valueCount)),
    m_ui(new Ui_ThemeWidgetForm) //ThemeWidgetForm is the ui class name, you can watch it in ui_themewidget.h
{
    m_ui->setupUi(this);
    populateThemeBox();
    populateAnimationBox();
    populateLegendBox();

    /*
    //create charts
    QChartView *chartView;

    chartView = new QChartView(createLineChart(), this);
    m_ui->gridLayout->addWidget(chartView, 1, 0);
    m_charts << chartView;  //m_charts is QList<QChartView *>

    chartView = new QChartView(createSplineChart(), this);
    m_ui->gridLayout->addWidget(chartView, 1, 1);
    m_charts << chartView;

    chartView = new QChartView(createSplineChart(), this);
    m_ui->gridLayout->addWidget(chartView, 1, 2);
    m_charts << chartView;

    chartView = new QChartView(createSplineChart(), this);
    m_ui->gridLayout->addWidget(chartView, 1, 3);
    m_charts << chartView;

    chartView = new QChartView(createSplineChart(), this);
    m_ui->gridLayout->addWidget(chartView, 2, 0);
    m_charts << chartView;

    chartView = new QChartView(createSplineChart(), this);
    m_ui->gridLayout->addWidget(chartView, 2, 1);
    m_charts << chartView;

    chartView = new QChartView(createSplineChart(), this);
    m_ui->gridLayout->addWidget(chartView, 2, 2);
    m_charts << chartView;
    */

    //create figure charts
    QChartView *chartView;
    //figure1
    chartView = new QChartView(createF1Chart(&(*figure_datatablemap)[tr("figure1")]), this);
    m_ui->gridLayout->addWidget(chartView, 1, 0);
    m_charts << chartView;  //m_charts is QList<QChartView *>
    //figre2
    chartView = new QChartView(createF2Chart(&(*figure_datatablemap)[tr("figure2")]), this);
    m_ui->gridLayout->addWidget(chartView, 1, 1);
    m_charts << chartView;
    //figure3
    chartView = new QChartView(createF3Chart(&(*figure_datatablemap)[tr("figure3")]), this);
    m_ui->gridLayout->addWidget(chartView, 1, 2);
    m_charts << chartView;
    //figure4
    chartView = new QChartView(createF4Chart(&(*figure_datatablemap)[tr("figure4")]), this);
    m_ui->gridLayout->addWidget(chartView, 1, 3);
    m_charts << chartView;
    //figure5
    chartView = new QChartView(createF5Chart(&(*figure_datatablemap)[tr("figure5")]), this);
    m_ui->gridLayout->addWidget(chartView, 2, 0);
    m_charts << chartView;
    //figure6
    chartView = new QChartView(createF6Chart(&(*figure_datatablemap)[tr("figure6")]), this);
    m_ui->gridLayout->addWidget(chartView, 2, 1);
    m_charts << chartView;
    //figure7
    chartView = new QChartView(createF7Chart(&(*figure_datatablemap)[tr("figure7")]), this);
    m_ui->gridLayout->addWidget(chartView, 2, 2);
    m_charts << chartView;


    // Set defaults
    m_ui->antialiasCheckBox->setChecked(true);
    m_ui->themeComboBox->setCurrentIndex(1);    //Blue Cerulean
    m_ui->animatedComboBox->setCurrentIndex(1); //All Animations

    updateUI();
}

ThemeWidget::~ThemeWidget()
{
    delete m_ui;
}

DataTable ThemeWidget::generateRandomData(int listCount, int valueMax, int valueCount) const
{   //the default value of listCount is 3, valueMax is 10, valueCout is 7
    DataTable dataTable;

    // generate random data
    //QRandomGenerator::global()->bounded(valueMax / (qreal) valueCount) generate [0, 1.428571...)
    //yValue + QRandomGenerator::global()->bounded(valueMax / (qreal) valueCount); The resulting value will not exceed the previous value plus 1.428571...

    // (j + QRandomGenerator::global()->generateDouble()) * ((qreal) 10 / (qreal) 7);  10/7=1.428571...
    // if j=0, generate [0, 1.428571..), include left, not include right
    // if j=1, j + QRandomGenerator::global()->generateDouble() generate [1,2), whole expression generate [1.428571..., 1.428571...*2)
    // if j=2, j + QRandomGenerator::global()->generateDouble() generate [2,3), whole expression generate [1.428571...*2, 1.428571...*3)
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        qreal yValue(0);
        for (int j(0); j < valueCount; j++) { //double QRandomGenerator::bounded(double highest), Generates one random double in the range between 0 (inclusive) and highest (exclusive).This function is equivalent to and is implemented as: return generateDouble() * highest;
            yValue = yValue + QRandomGenerator::global()->bounded(valueMax / (qreal) valueCount);  //double QRandomGenerator::generateDouble(), Generates one random qreal in the canonical range [0, 1) (that is, inclusive of zero and exclusive of 1).
            QPointF value((j + QRandomGenerator::global()->generateDouble()) * ((qreal) m_valueMax / (qreal) valueCount),
                          yValue);
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        dataTable << dataList;
    }

    return dataTable;
}

void ThemeWidget::populateThemeBox()
{
    // add items to theme combobox
    m_ui->themeComboBox->addItem("Light", QChart::ChartThemeLight);
    m_ui->themeComboBox->addItem("Blue Cerulean", QChart::ChartThemeBlueCerulean);
    m_ui->themeComboBox->addItem("Dark", QChart::ChartThemeDark);
    m_ui->themeComboBox->addItem("Brown Sand", QChart::ChartThemeBrownSand);
    m_ui->themeComboBox->addItem("Blue NCS", QChart::ChartThemeBlueNcs);
    m_ui->themeComboBox->addItem("High Contrast", QChart::ChartThemeHighContrast);
    m_ui->themeComboBox->addItem("Blue Icy", QChart::ChartThemeBlueIcy);
    m_ui->themeComboBox->addItem("Qt", QChart::ChartThemeQt);
}

void ThemeWidget::populateAnimationBox()
{
    // add items to animation combobox
    m_ui->animatedComboBox->addItem("No Animations", QChart::NoAnimation);
    m_ui->animatedComboBox->addItem("GridAxis Animations", QChart::GridAxisAnimations);
    m_ui->animatedComboBox->addItem("Series Animations", QChart::SeriesAnimations);
    m_ui->animatedComboBox->addItem("All Animations", QChart::AllAnimations);

}

void ThemeWidget::populateLegendBox()
{
    // add items to legend combobox
    m_ui->legendComboBox->addItem("No Legend ", 0);
    m_ui->legendComboBox->addItem("Legend Top", Qt::AlignTop);
    m_ui->legendComboBox->addItem("Legend Bottom", Qt::AlignBottom);
    m_ui->legendComboBox->addItem("Legend Left", Qt::AlignLeft);
    m_ui->legendComboBox->addItem("Legend Right", Qt::AlignRight);
}

//QChart *ThemeWidget::createLineChart() const
//{
//    //![1]
//    auto chart = new QChart;
//    chart->setTitle("Line Chart");
//    //![1]

//    //![2]
//    QString name("Series ");  //1.typedef QPair<QPointF, QString> Data; 2.typedef QList<Data> DataList; 3.typedef QList<DataList> DataTable;
//    int nameIndex = 0;
//    for (const DataList &list : m_dataTable) { //DataTable m_dataTable; colon iteration, if want modify parameters value must use ref pass
//        auto series = new QLineSeries(chart);
//        for (const Data &data : list)
//            series->append(data.first);  //data.first is QPointF. item of series use *series << QPointF(11, 1) or series->append(7, 4); The two values represent the horizontal and vertical coordinates respectively
//        series->setName(name + QString::number(nameIndex));
//        nameIndex++;    //m_dataTable is list of list. it has 3 list.
//        chart->addSeries(series);  // a series represent a line, has 3 lines, then the chart has 3 series
//    }
//    //![2]

//    //![3]
//    chart->createDefaultAxes();
//    chart->axes(Qt::Horizontal).first()->setRange(0, m_valueMax);  //Horizontal range
//    chart->axes(Qt::Vertical).first()->setRange(0, m_valueCount);  //Vertical range
//    //![3]
//    //![4]
//    // Add space to label to add space between labels and axis
//    auto axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
//    Q_ASSERT(axisY);
//    axisY->setLabelFormat("%.1f  ");  //set the style of scale
//    //axisY->setLabelFormat("%.4f      ");  //
//    //axisY->setLabelsVisible(false);  //Vertical scale invisible
//    //axisY->setGridLineVisible(false);  //Vertical gridline invisible
//    //![4]

//    return chart;
//}

void ThemeWidget::updateUI()
{
    //![6]
    auto theme = static_cast<QChart::ChartTheme>(
        m_ui->themeComboBox->itemData(m_ui->themeComboBox->currentIndex()).toInt());  //through index get itemData, then cast to int
    //![6]
    const auto charts = m_charts;  //m_charts is QList<QChartView *>
    if (!m_charts.isEmpty() && m_charts.at(0)->chart()->theme() != theme) {
        for (QChartView *chartView : charts) {
            //![7]
            chartView->chart()->setTheme(theme);
            //![7]
        }
    }

    // Update antialiasing
    //![11]
    bool checked = m_ui->antialiasCheckBox->isChecked();
    for (QChartView *chartView : charts)
        chartView->setRenderHint(QPainter::Antialiasing, checked);
    //![11]

    // Update animation options
    //![9]
    QChart::AnimationOptions options(
        m_ui->animatedComboBox->itemData(m_ui->animatedComboBox->currentIndex()).toInt());
    if (!m_charts.isEmpty() && m_charts.at(0)->chart()->animationOptions() != options) {
        for (QChartView *chartView : charts)
            chartView->chart()->setAnimationOptions(options);
    }
    //![9]

    // Update legend alignment
    //![10]
    Qt::Alignment alignment(
        m_ui->legendComboBox->itemData(m_ui->legendComboBox->currentIndex()).toInt());

    if (!alignment) {  //if alignment==0
        for (QChartView *chartView : charts)
            chartView->chart()->legend()->hide();
    } else {
        for (QChartView *chartView : charts) {
            chartView->chart()->legend()->setAlignment(alignment);
            chartView->chart()->legend()->show();
        }
    }
    //![10]
}

QChart *ThemeWidget::createF1Chart(DataTable* figure_datatable) const
{
    auto chart = new QChart;
    chart->setTitle("Fig.1 导带电子波函数");

    QString name(QString::fromUtf8("\xCF\x88"));
    int nameIndex = 1;
    if(!figure_datatable->isEmpty())
    {
        for(const DataList &list : *figure_datatable){
            auto series = new QLineSeries(chart);
            for (const Data &data : list)
                series->append(data.first);
            series->setName(name + QString::number(nameIndex));
            nameIndex++;
            chart->addSeries(series);
        }
    }
    else{
        auto series = new QLineSeries(chart);
        chart->addSeries(series);
    }

    chart->createDefaultAxes();  //based on series
    chart->axes(Qt::Horizontal).first()->setRange(-30, 30);  //Horizontal range
    chart->axes(Qt::Vertical).first()->setRange(-0.1, 0.04);  //Vertical range
    // Add space to label to add space between labels and axis
    auto axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.2f  ");  //set the style of scale
    axisY->setTitleText(QString::fromUtf8("\xCF\x88"));  //axisY title

    auto axisX = qobject_cast<QValueAxis *>(chart->axes(Qt::Horizontal).first());
    Q_ASSERT(axisX);
    axisX->setTitleText("Position[nm]");

    return chart;
}

QChart *ThemeWidget::createF2Chart(DataTable* figure_datatable) const
{
    auto chart = new QChart;
    chart->setTitle("Fig.2 导带电子能量色散关系");

    QString name("C");
    int nameIndex = 1;
    if(!figure_datatable->isEmpty())
    {
        for(const DataList &list : *figure_datatable){
            auto series = new QLineSeries(chart);
            for (const Data &data : list)
                series->append(data.first);
            series->setName(name + QString::number(nameIndex));
            nameIndex++;
            chart->addSeries(series);
        }
    }
    else{
        auto series = new QLineSeries(chart);
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, 0.08);  //Horizontal range
    chart->axes(Qt::Vertical).first()->setRange(1.2, 1.8);  //Vertical range
    // Add space to label to add space between labels and axis
    auto axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");  //set the style of scale
    axisY->setTitleText("E[eV]");  //axisY title

    auto axisX = qobject_cast<QValueAxis *>(chart->axes(Qt::Horizontal).first());
    Q_ASSERT(axisX);
    axisX->setTitleText(QString::fromUtf8("k\xE2\x82\x9C[1/10\xE2\x81\xBB\xC2\xB9\xC2\xBA")+"m]");

    return chart;
}

QChart *ThemeWidget::createF3Chart(DataTable* figure_datatable) const
{
    auto chart = new QChart;
    chart->setTitle("Fig.3 价带空穴能量色散关系");

    QString name("HH");  //first three is begin of 'HH', last one begin of 'LH'
    int nameIndex = 1;
    if(!figure_datatable->isEmpty())
    {
        for(const DataList &list : *figure_datatable){
            auto series = new QLineSeries(chart);
            for (const Data &data : list)
                series->append(data.first);
            if(nameIndex<4)
                series->setName(name + QString::number(nameIndex));
            else
                series->setName("LH1");
            nameIndex++;
            chart->addSeries(series);
        }
    }
    else{
        auto series = new QLineSeries(chart);
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, 0.08);  //Horizontal range
    chart->axes(Qt::Vertical).first()->setRange(-120, 20);  //Vertical range
    // Add space to label to add space between labels and axis
    auto axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.0f  ");  //set the style of scale
    axisY->setTitleText("E[meV]");  //axisY title

    auto axisX = qobject_cast<QValueAxis *>(chart->axes(Qt::Horizontal).first());
    Q_ASSERT(axisX);
    axisX->setLabelFormat("%.2f  ");  //set the style of scale
    axisX->setTitleText(QString::fromUtf8("k\xE2\x82\x9C[1/10\xE2\x81\xBB\xC2\xB9\xC2\xBA")+"m]");

    return chart;
}

QChart *ThemeWidget::createF4Chart(DataTable* figure_datatable) const
{
    auto chart = new QChart;
    chart->setTitle("Fig.4 量子阱材料增益谱");

    //QString name("HH");  //first three is begin of 'HH', last one begin of 'LH'
    //int nameIndex = 1;
    if(!figure_datatable->isEmpty())
    {
        for(const DataList &list : *figure_datatable){
            auto series = new QLineSeries(chart);
            for (const Data &data : list)
                series->append(data.first);
            //series->setName(name + QString::number(nameIndex));
            //nameIndex++;
            chart->addSeries(series);
        }
    }
    else{
        auto series = new QLineSeries(chart);
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(850, 1150);  //Horizontal range
    chart->axes(Qt::Vertical).first()->setRange(-2000, 3000);  //Vertical range
    // Add space to label to add space between labels and axis
    auto axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.0f  ");  //set the style of scale
    axisY->setTitleText("Gain[1/cm]");  //axisY title

    auto axisX = qobject_cast<QValueAxis *>(chart->axes(Qt::Horizontal).first());
    Q_ASSERT(axisX);
    axisX->setLabelFormat("%.0f  ");  //set the style of scale
    axisX->setTitleText("Wavelength[nm]");


    return chart;
}

QChart *ThemeWidget::createF5Chart(DataTable* figure_datatable) const
{
    auto chart = new QChart;
    chart->setTitle("Fig.5 DBR反射谱");

    //QString name("HH");  //first three is begin of 'HH', last one begin of 'LH'
    //int nameIndex = 1;
    if(!figure_datatable->isEmpty())
    {
        for(const DataList &list : *figure_datatable){
            auto series = new QLineSeries(chart);
            for (const Data &data : list)
                series->append(data.first);
            //series->setName(name + QString::number(nameIndex));
            //nameIndex++;
            chart->addSeries(series);
        }
    }
    else{
        auto series = new QLineSeries(chart);
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(850, 1150);  //Horizontal range
    chart->axes(Qt::Vertical).first()->setRange(0, 100);       //Vertical range
    // Add space to label to add space between labels and axis
    auto axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.0f  ");  //set the style of scale
    axisY->setTitleText("Reflectivity[%]");  //axisY title

    auto axisX = qobject_cast<QValueAxis *>(chart->axes(Qt::Horizontal).first());
    Q_ASSERT(axisX);
    axisX->setLabelFormat("%.0f  ");  //set the style of scale
    axisX->setTitleText("Wavelength[nm]");

    return chart;
}

QChart *ThemeWidget::createF6Chart(DataTable* figure_datatable) const
{
    auto chart = new QChart;
    chart->setTitle("Fig.6 增益芯片内部驻波场电场分布");

    /*
    //QString name("HH");  //first three is begin of 'HH', last one begin of 'LH'
    //int nameIndex = 1;
    for(const DataList &list : *figure_datatable){
        auto series = new QLineSeries(chart);
        for (const Data &data : list)
            series->append(data.first);
        //series->setName(name + QString::number(nameIndex));
        //nameIndex++;
        chart->addSeries(series);
    }
    */

    //QString name("figure6_");  //first three is begin of 'HH', last one begin of 'LH'
    int listcount = 0;
    double mm1 = 1;
    //int nameIndex = 1;
    if(!figure_datatable->isEmpty())
    {
        listcount = figure_datatable->count();
        for(int i(0); i<listcount-1; i++){  //i<listcount-1 except last list
            const DataList &list = figure_datatable->at(i);
            auto series = new QLineSeries(chart);
            for (const Data &data : list)
                series->append(data.first);
            //series->setName(name + QString::number(nameIndex));
            //nameIndex++;
            chart->addSeries(series);
        }
        mm1 = (figure_datatable->at(listcount-1)).at(0).first.y();
    }
    else{
        auto series = new QLineSeries(chart);
        chart->addSeries(series);
    }

    //figure_datatable->at(listcount-1) get list
    //at(0) get first data in list
    //.first get QPointF
    // .y() get second value in QPointF

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(0, 4800);  //Horizontal range
    chart->axes(Qt::Vertical).first()->setRange(0, 4.5);       //Vertical range
    // Add space to label to add space between labels and axis
    auto axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.1f  ");  //set the style of scale
    axisY->setTitleText("|A|" + QString::fromUtf8("\xC2\xB2"));  //axisY title

    auto axisX = qobject_cast<QValueAxis *>(chart->axes(Qt::Horizontal).first());
    Q_ASSERT(axisX);
    axisX->setLabelFormat("%.0f  ");  //set the style of scale
    axisX->setTitleText("Position[nm]");

    //according to matlab process
    if (int(mm1*4) % 2 == 1)
        chart->axes(Qt::Vertical).first()->setRange(0, 0.6);

    if (int(mm1*8) % 2 == 1)
        chart->axes(Qt::Vertical).first()->setRange(0, 1);

    return chart;
}

QChart *ThemeWidget::createF7Chart(DataTable* figure_datatable) const
{
    auto chart = new QChart;
    chart->setTitle("Fig.7 增益芯片纵模限制因子");

    //QString name("HH");  //first three is begin of 'HH', last one begin of 'LH'
    //int nameIndex = 1;
    if(!figure_datatable->isEmpty())
    {
        for(const DataList &list : *figure_datatable){
            auto series = new QLineSeries(chart);
            for (const Data &data : list)
                series->append(data.first);
            //series->setName(name + QString::number(nameIndex));
            //nameIndex++;
            chart->addSeries(series);
        }
    }
    else{
        auto series = new QLineSeries(chart);
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
    chart->axes(Qt::Horizontal).first()->setRange(850, 1150);  //Horizontal range
    chart->axes(Qt::Vertical).first()->setRange(0, 25);       //Vertical range
    // Add space to label to add space between labels and axis
    auto axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.0f  ");  //set the style of scale
    axisY->setTitleText("Intensity[a.u.]");  //axisY title

    auto axisX = qobject_cast<QValueAxis *>(chart->axes(Qt::Horizontal).first());
    Q_ASSERT(axisX);
    axisX->setLabelFormat("%.0f  ");  //set the style of scale
    axisX->setTitleText("Wavelength[nm]");

    return chart;
}

