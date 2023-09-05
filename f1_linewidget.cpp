#include "f1_linewidget.h"
#include <QLineSeries>
#include <QValueAxis>

F1_LineWidget::F1_LineWidget(QWidget *parent, DataTable* figure_datatable) : ContentWidget(parent)  //parent: QWidget->ConetentWidget->LineWidget
{

    /*
    //![1]
    auto series = new QLineSeries;
    //![1]

    //![2]
    series->append(0, 6);
    series->append(2, 4);
    series->append(3, 8);
    series->append(7, 4);
    series->append(10, 5);
    *series << QPointF(11, 1) << QPointF(13, 3) << QPointF(17, 6) << QPointF(18, 3) << QPointF(20, 2);
    //![2]

    //![3]
    auto chart = new QChart;
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->setTitle("Simple Line Chart");
    //![3]

    //![4]
    createDefaultChartView(chart);  //createDefaultChartView is in the ContentWidget class, which is the base class for LineWidget
    //![4]
    */

    auto chart = new QChart;
    chart->setTitle("Find lowest nmodes eigenvectors and eigenvalues of sparse matrix");

    QString name(QString::fromUtf8("\xCF\x88"));  //phi, http://www.kreativekorp.com/charset/unicode/
    int nameIndex = 0;
    for(const DataList &list : *figure_datatable){
        auto series = new QLineSeries(chart);
        for (const Data &data : list)
            series->append(data.first);
        series->setName(name + QString::number(nameIndex));
        nameIndex++;
        chart->addSeries(series);
    }

    chart->createDefaultAxes();
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

    createDefaultChartView(chart);

}
