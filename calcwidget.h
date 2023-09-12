/*******************************************************************
* This file was created in Chongqing in 2023-09-12 09:09:28.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/

#ifndef CALCWIDGET_H
#define CALCWIDGET_H

#include <QWidget>
#include <QCloseEvent>
#include <QLabel>
#include "calcmatlabthread.h"
#include "mainwidget.h"

class CalcWidget : public QWidget
{
    Q_OBJECT
public:
    //explicit CalcWidget(QWidget *parent = nullptr, MainWidget *p_mainwidget = nullptr);
    explicit CalcWidget(MainWidget *p_mainwidget = nullptr);
    double m_ArrInParams[12];

private:
    QLabel *m_pCautionLabel = nullptr;
    QLabel *m_pPicLabel = nullptr;
    CalcMatlabThread *m_thread = nullptr;
    bool m_calcDone = false;
    MainWidget *m_pmainwidget = nullptr;

private slots:
    void closeEvent(QCloseEvent*);
    void doMatlabDone(const QString info, const FigureData figure_datatablemap);

signals:

};

#endif // CALCWIDGET_H
