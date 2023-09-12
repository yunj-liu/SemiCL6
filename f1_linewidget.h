/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:39.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#ifndef F1_LINEWIDGET_H
#define F1_LINEWIDGET_H

#include "contentwidget.h"
#include "commoncontrol.h"

class F1_LineWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit F1_LineWidget(QWidget *parent = nullptr, DataTable* figure_datatable = nullptr);
};

#endif // F1_LINEWIDGET_H
