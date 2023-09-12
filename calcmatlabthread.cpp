/*******************************************************************
* This file was created in Chongqing in 2023-09-12 14:23:54.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/

#include "calcmatlabthread.h"
#include "commoncontrol.h"

CalcMatlabThread::CalcMatlabThread(QObject *parent, double(*pArrInParams)[12]) : QThread(parent)
{
    m_pArrInParams = pArrInParams;
}

void CalcMatlabThread::run(){
    /*
    qDebug() << (*m_pArrInParams)[0];
    qDebug() << (*m_pArrInParams)[1];
    qDebug() << (*m_pArrInParams)[2];
    qDebug() << (*m_pArrInParams)[3];
    qDebug() << (*m_pArrInParams)[4];
    qDebug() << (*m_pArrInParams)[5];
    qDebug() << (*m_pArrInParams)[6];
    qDebug() << (*m_pArrInParams)[7];
    qDebug() << (*m_pArrInParams)[8];
    qDebug() << (*m_pArrInParams)[9];
    qDebug() << (*m_pArrInParams)[10];
    qDebug() << (*m_pArrInParams)[11];
    */

    //call matlab
    m_datatableMap = CommonControl::generateFigureData(m_pArrInParams);

    emit SendMatlabDoneInfo(QString("Dll done."), m_datatableMap);
}
