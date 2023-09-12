/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:39.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#ifndef F2_LINEWIDGET_H
#define F2_LINEWIDGET_H

#include "contentwidget.h"
#include "commoncontrol.h"

class F2_LineWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit F2_LineWidget(QWidget *parent = nullptr, DataTable* figure_datatable = nullptr);
};

#endif // F2_LINEWIDGET_H
