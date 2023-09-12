/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:39.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#ifndef COMMONTYPE_H
#define COMMONTYPE_H
#include <QWidget>

typedef QPair<QPointF, QString> Data;  //need include QWidget
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;
typedef QHash<QString, DataTable> FigureData;

#endif // COMMONTYPE_H
