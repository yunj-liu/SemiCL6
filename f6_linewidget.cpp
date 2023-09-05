#include "f6_linewidget.h"
#include <QLineSeries>
#include <QValueAxis>

F6_LineWidget::F6_LineWidget(QWidget *parent, DataTable* figure_datatable) : ContentWidget(parent)
{
    auto chart = new QChart;
    chart->setTitle("VECSEL驻波场电场分布");

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

    QString name("figure6_");  //first three is begin of 'HH', last one begin of 'LH'
    int nameIndex = 1;
    int listcount = figure_datatable->count();
    for(int i(0); i<listcount-1; i++){  //i<listcount-1 except last list
        const DataList &list = figure_datatable->at(i);
        auto series = new QLineSeries(chart);
        for (const Data &data : list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }

    //figure_datatable->at(listcount-1) get list
    //at(0) get first data in list
    //.first get QPointF
    // .y() get second value in QPointF
    double mm1 = (figure_datatable->at(listcount-1)).at(0).first.y();

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

    chart->legend()->hide();

    createDefaultChartView(chart);
}
