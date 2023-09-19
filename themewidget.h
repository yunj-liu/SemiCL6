/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:39.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include "contentwidget.h"
#include <QChart>
#include <QChartView>
#include "commoncontrol.h"
#include <QGroupBox>
#include <QLineEdit>
#include <QRadioButton>

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
    //QChart *createLineChart() const;
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

    //8
    QLineEdit *lineedit1;
    QLineEdit *lineedit2;
    QLineEdit *lineedit3;
    QLineEdit *lineedit4;
    QLineEdit *lineedit5;
    QLineEdit *lineedit6;

    QRadioButton *radiog41;
    QRadioButton *radiog42;
    QRadioButton *radiog43;
    QRadioButton *radiog51;
    QRadioButton *radiog52;
    QRadioButton *radiog61;
    QRadioButton *radiog62;
    QRadioButton *radiog63;
    QRadioButton *radiog71;
    QRadioButton *radiog72;
    QRadioButton *radiog73;
    QRadioButton *radiog81;
    QRadioButton *radiog82;
    QRadioButton *radiog83;
    QRadioButton *radiog91;
    QRadioButton *radiog92;

    QButtonGroup *btnGroup4;
    QButtonGroup *btnGroup5;
    QButtonGroup *btnGroup6;
    QButtonGroup *btnGroup7;
    QButtonGroup *btnGroup8;
    QButtonGroup *btnGroup9;


private:
    int m_listCount;
    int m_valueMax;
    int m_valueCount;
    QList<QChartView *> m_charts;
    //DataTable m_dataTable;

    Ui_ThemeWidgetForm *m_ui;
};

#endif // THEMEWIDGET_H
