/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:39.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#include "f3_linewidget.h"
#include <QLineSeries>
#include <QValueAxis>

F3_LineWidget::F3_LineWidget(QWidget *parent, DataTable* figure_datatable) : ContentWidget(parent)
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
    //chart->axes(Qt::Horizontal).first()->setRange(0, 0.08);  //Horizontal range
    //chart->axes(Qt::Vertical).first()->setRange(-120, 20);  //Vertical range
    // Add space to label to add space between labels and axis
    auto axisY = qobject_cast<QValueAxis *>(chart->axes(Qt::Vertical).first());
    Q_ASSERT(axisY);
    axisY->setLabelFormat("%.0f  ");  //set the style of scale
    axisY->setTitleText("E[meV]");  //axisY title

    auto axisX = qobject_cast<QValueAxis *>(chart->axes(Qt::Horizontal).first());
    Q_ASSERT(axisX);
    axisX->setLabelFormat("%.2f  ");  //set the style of scale
    axisX->setTitleText(QString::fromUtf8("k\xE2\x82\x9C[1/10\xE2\x81\xBB\xC2\xB9\xC2\xBA")+"m]");


    createDefaultChartView(chart);
}
