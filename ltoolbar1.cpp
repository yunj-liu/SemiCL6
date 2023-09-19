/*******************************************************************
* This file was created in Chongqing in 2023-09-10 20:50:22.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#include "ltoolbar1.h"
#include <QApplication>  //qApp need <QApplication>

LToolBar1::LToolBar1(const QString &title, MainWindow *mainWindow)
{
    setWindowTitle(title);
    setObjectName(title);
    setIconSize(QSize(32, 32));
    //setIconSize(QSize(24, 24));

    mResetAction = addAction(QIcon(":/imgs/update-left-rotation-64.png"), QString("恢复默认值"));
    connect(mResetAction, &QAction::triggered, mainWindow, &MainWindow::resetCalcParams);

    mSetCalcParamAction = addAction(QIcon(":/imgs/mechanistic-analysis-60.png"), QString("设置运算参数"));  // add a action in this toolbar
    connect(mSetCalcParamAction, &QAction::triggered, mainWindow, &MainWindow::setCalcParams);

    mSep1 = addSeparator();

    mCalcAction = addAction(QIcon(":/imgs/sort-green-right-90.png"), QString("重新计算"));
    connect(mCalcAction, &QAction::triggered, mainWindow, &MainWindow::matlabCalc);

    mSep1 = addSeparator();

    mLeftarrowAction = addAction(QIcon(":/imgs/left-60.png"), QString("上一个"));
    connect(mLeftarrowAction, &QAction::triggered, mainWindow, &MainWindow::upFigure);

    mRightarrowAction = addAction(QIcon(":/imgs/right-60.png"), QString("下一个"));
    connect(mRightarrowAction, &QAction::triggered, mainWindow, &MainWindow::nextFigure);

    mSep1 = addSeparator();

    mInfoAction = addAction(QIcon(":/imgs/info-60.png"), QString("关于"));

    mSep1 = addSeparator();

    mExitAction = addAction(QIcon(":/imgs/exit-90.png"), QString("退出"));
    connect(mExitAction, &QAction::triggered, qApp, &QCoreApplication::quit);


}
