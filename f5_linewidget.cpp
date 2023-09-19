/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:39.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#include "f5_linewidget.h"
#include <QLineSeries>
#include <QValueAxis>

F5_LineWidget::F5_LineWidget(QWidget *parent, DataTable* figure_datatable, QChart::ChartTheme ct, QChart::AnimationOption ao) : ContentWidget(parent)
{
    auto chart = new QChart;
    chart->setTitle("Fig.5 DBR反射谱");
    //set theme
    chart->setTheme(ct);
    //set animation option
    chart->setAnimationOptions(ao);

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
    //chart->axes(Qt::Horizontal).first()->setRange(850, 1150);  //Horizontal range
    //chart->axes(Qt::Vertical).first()->setRange(0, 100);       //Vertical range
    // Add space to label to add space between labels and axis
    auto axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.0f  ");  //set the style of scale
    axisY->setTitleText("Reflectivity[%]");  //axisY title

    auto axisX = qobject_cast<QValueAxis *>(chart->axes(Qt::Horizontal).first());
    Q_ASSERT(axisX);
    axisX->setLabelFormat("%.0f  ");  //set the style of scale
    axisX->setTitleText("Wavelength[nm]");

    chart->legend()->hide();

    createDefaultChartView(chart);
}
