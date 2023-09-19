/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:39.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#ifndef F7_LINEWIDGET_H
#define F7_LINEWIDGET_H

#include "contentwidget.h"
#include "commoncontrol.h"

class F7_LineWidget : public ContentWidget
{
    Q_OBJECT
public:
    F7_LineWidget(QWidget *parent = nullptr, DataTable* figure_datatable = nullptr, QChart::ChartTheme ct=QChart::ChartThemeLight, QChart::AnimationOption ao = QChart::NoAnimation);
};

#endif // F7_LINEWIDGET_H
