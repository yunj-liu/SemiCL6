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

    mCalcAction = addAction(QIcon(":/imgs/play-60.png"), QString("重新计算"));
    connect(mCalcAction, &QAction::triggered, mainWindow, &MainWindow::matlabCalc);

    mSep1 = addSeparator();

    mLeftarrowAction = addAction(QIcon(":/imgs/back-to-48.png"), QString("上一个"));
    connect(mLeftarrowAction, &QAction::triggered, mainWindow, &MainWindow::upFigure);

    mRightarrowAction = addAction(QIcon(":/imgs/next-page-48.png"), QString("下一个"));
    connect(mRightarrowAction, &QAction::triggered, mainWindow, &MainWindow::nextFigure);

    mSep1 = addSeparator();

    mFiguresSaveAction = addAction(QIcon(":/imgs/save-all-48.png"), QString("图表数据保存"));
    connect(mFiguresSaveAction, &QAction::triggered, mainWindow, &MainWindow::figuresSave);

    mFiguresSaveasAction = addAction(QIcon(":/imgs/save-as-94.png"), QString("图表数据另存为"));
    connect(mFiguresSaveasAction, &QAction::triggered, mainWindow, &MainWindow::figuresSaveAs);

    mSep1 = addSeparator();

    mEpStrucReportAction = addAction(QIcon(":/imgs/chip-60.png"), QString("芯片外延结构"));
    connect(mEpStrucReportAction, &QAction::triggered, mainWindow, &MainWindow::epitaxyStruct);

    mRidxReportAction = addAction(QIcon(":/imgs/refraction-48.png"), QString("外延材料折射率"));
    connect(mRidxReportAction, &QAction::triggered, mainWindow, &MainWindow::refractiveIndex);

    mSep1 = addSeparator();

    mAboutAction = addAction(QIcon(":/imgs/about-60.png"), QString("关于"));  //color code:#743391
    connect(mAboutAction, &QAction::triggered, mainWindow, &MainWindow::about);

    mSep1 = addSeparator();

    mExitAction = addAction(QIcon(":/imgs/exit-90.png"), QString("退出"));
    connect(mExitAction, &QAction::triggered, qApp, &QCoreApplication::quit);


}
