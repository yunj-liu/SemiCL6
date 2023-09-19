/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:39.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QHash>
#include <QWidget>  //Actually in contentwidget.h There have been include QWidget,but QWidget have #ifndef, so don't worry about including one more time again
#include <QListView>  // without using QT_FORWARD_DECLARE_CLASS instead of using #include
#include <QStringListModel>

#include "contentwidget.h"  //without using 'class ContentWidget', it's equivalent to QT_FORWARD_DECLARE_CLASS
#include "commoncontrol.h"

class MainWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainWidget(QWidget *parent = nullptr, QChart::ChartTheme ct = QChart::ChartThemeLight, QChart::AnimationOption ao = QChart::NoAnimation);
    ~MainWidget();
    void refershChartThemes();
    int getListviewCurrentIndex();
    void setActiveWithIndex(int index=0, QChart::ChartTheme ct=QChart::ChartThemeLight, QChart::AnimationOption ao = QChart::NoAnimation);


protected:
    void resizeEvent(QResizeEvent *) override;

private:
    enum Example{
        ChartThemes,
        F1_LineChart,
        F2_LineChart,
        F3_LineChart,
        F4_LineChart,
        F5_LineChart,
        F6_LineChart,
        F7_LineChart
    };

    void setActiveExample(Example example);  //no ct param, use m_ct
    QListView *m_listView = nullptr;
    QStringListModel *m_listModel = nullptr;
    QWidget *m_contentArea = nullptr;
    ContentWidget *m_activeWidget = nullptr;
    QHash<QString, Example> m_exampleMap;
    //call dll
    FigureData m_datatableMap;
    //FigureData generateFigureData() const;

    QStringList examples;  // let examples be member
    QChart::ChartTheme m_ct = QChart::ChartThemeLight;
    QChart::AnimationOption m_ao = QChart::NoAnimation;

public slots:
    void doMatlabDone(const QString info, const FigureData figure_datatablemap);

};
#endif // MAINWIDGET_H
