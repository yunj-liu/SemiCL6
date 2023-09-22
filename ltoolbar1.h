/*******************************************************************
* This file was created in Chongqing in 2023-09-10 20:50:10.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#ifndef LTOOLBAR1_H
#define LTOOLBAR1_H

#include <QToolBar>
#include "mainwindow.h"

class LToolBar1 : public QToolBar
{
    Q_OBJECT
public:
    explicit LToolBar1(const QString &title, MainWindow *mainWindow);

private:
    QAction *mSetCalcParamAction;
    QAction *mCalcAction;
    QAction *mResetAction;
    QAction *mRightarrowAction;
    QAction *mLeftarrowAction;
    QAction *mSep1;
    QAction *mAboutAction;
    QAction *mExitAction;
    QAction *mFiguresSaveAction;
    QAction *mFiguresSaveasAction;


};

#endif // LTOOLBAR1_H
