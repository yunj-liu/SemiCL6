#include "f7_linewidget.h"
#include <QLineSeries>
#include <QValueAxis>

F7_LineWidget::F7_LineWidget(QWidget *parent, DataTable* figure_datatable) : ContentWidget(parent)
{
    auto chart = new QChart;
    chart->setTitle("VECSEL纵模限制因子");

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

    chart->legend()->hide();

    createDefaultChartView(chart);
}
