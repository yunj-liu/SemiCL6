/*******************************************************************
* This file was created in Chongqing in 2023-09-12 14:23:47.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/

#ifndef CALCMATLABTHREAD_H
#define CALCMATLABTHREAD_H

#include <QThread>
#include "commontype.h"

class CalcMatlabThread : public QThread
{
    Q_OBJECT
public:
    CalcMatlabThread(QObject *parent = nullptr, double(*pArrInParams)[12] = nullptr);
    void run() override;

private:
    double(*m_pArrInParams)[12] = nullptr;
    FigureData m_datatableMap;

signals:
    void SendMatlabDoneInfo(const QString info, const FigureData figure_datatablemap);
};

#endif // CALCMATLABTHREAD_H
