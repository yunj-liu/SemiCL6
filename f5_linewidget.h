/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:39.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#ifndef F5_LINEWIDGET_H
#define F5_LINEWIDGET_H

#include "contentwidget.h"
#include "commoncontrol.h"

class F5_LineWidget : public ContentWidget
{
    Q_OBJECT
public:
    F5_LineWidget(QWidget *parent = nullptr, DataTable* figure_datatable = nullptr, QChart::ChartTheme ct=QChart::ChartThemeLight, QChart::AnimationOption ao = QChart::NoAnimation);
};

#endif // F5_LINEWIDGET_H
