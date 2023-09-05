#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include "contentwidget.h"
#include <QChart>
#include <QChartView>
#include "commontype.h"

QT_FORWARD_DECLARE_CLASS(Ui_ThemeWidgetForm);  //the name 'ThemeWidgetForm' is pick up when design ui,*.ui open with plain editor can watch it


class ThemeWidget: public ContentWidget
{
    Q_OBJECT
public:
    explicit ThemeWidget(QWidget *parent = nullptr, FigureData *figure_datatablemap = nullptr);
    ~ThemeWidget();

private slots:
    void updateUI();

private:
    DataTable generateRandomData(int listCount, int valueMax, int valueCount) const;
    void populateThemeBox();
    void populateAnimationBox();
    void populateLegendBox();
    void connectSignals();  //No implement, instead of use themewidget.ui
    QChart *createAreaChart() const;
    QChart *createBarChart(int valueCount) const;
    QChart *createPieChart() const;
    QChart *createLineChart() const;
    QChart *createSplineChart() const;
    QChart *createScatterChart() const;
    //figure
    QChart *createF1Chart(DataTable* figure_datatable = nullptr) const;
    QChart *createF2Chart(DataTable* figure_datatable = nullptr) const;
    QChart *createF3Chart(DataTable* figure_datatable = nullptr) const;
    QChart *createF4Chart(DataTable* figure_datatable = nullptr) const;
    QChart *createF5Chart(DataTable* figure_datatable = nullptr) const;
    QChart *createF6Chart(DataTable* figure_datatable = nullptr) const;
    QChart *createF7Chart(DataTable* figure_datatable = nullptr) const;


private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    QList<QChartView *> m_charts;
    DataTable m_dataTable;

    Ui_ThemeWidgetForm *m_ui;
};

#endif // THEMEWIDGET_H
