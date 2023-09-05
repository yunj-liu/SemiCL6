#include "f2_linewidget.h"
#include <QLineSeries>
#include <QValueAxis>

F2_LineWidget::F2_LineWidget(QWidget *parent, DataTable* figure_datatable) : ContentWidget(parent)
{
    auto chart = new QChart;
    chart->setTitle("energy dispersion of conduction");

    QString name("C");
    int nameIndex = 1;
    for(const DataList &list : *figure_datatable){
        auto series = new QLineSeries(chart);
        for (const Data &data : list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
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


    createDefaultChartView(chart);
}
