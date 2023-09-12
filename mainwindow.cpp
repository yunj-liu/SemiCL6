/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:26.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/

#include "mainwindow.h"
#include <QStatusBar>
#include <QApplication>  //qApp need this include
#include <QMenu>
#include <QMenuBar>
#include "ltoolbar.h"



MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    //qApp->setApplicationDisplayName(tr("SemiCL - NCAMCQ"));  //instead of setWindowTitle
    setObjectName("MainWindow");
    setWindowTitle("SemiCL - NCAMCQ");

    createMenuBar();
    createToolBar();

    //CentralWidget
    m_pMainWidget = new MainWidget(this);
    setCentralWidget(m_pMainWidget);

    statusBar()->showMessage(QString("启动."));


}

void MainWindow::createMenuBar()
{
    //File menu
    mpFileMenu = menuBar()->addMenu(QString("文件(&F)"));
    mpFileMenu->addAction(QString("Save layout..."), this, &MainWindow::saveLayout);
    mpFileMenu->addAction(QString("Load layout..."), this, &MainWindow::loadLayout);
    mpFileMenu->addAction(QString("Switch layout direction"),this, &MainWindow::switchLayoutDirection);
    mpFileMenu->addSeparator();
    mpFileMenu->addAction(QIcon(":/imgs/exit-90.png"), QString("&Quit"), qApp, &QCoreApplication::quit);

    //Calc menu
    mpCalcMenu = menuBar()->addMenu(QString("计算(&C)"));
    mpCalcMenu->addAction(QIcon(":/imgs/formula-fx-100.png"), QString("参数设置..."), this, &MainWindow::setCalcParams);
    mpCalcMenu->addSeparator();
    mpCalcMenu->addAction(QIcon(":/imgs/sort-green-right-90.png"), QString("计算"), this, &MainWindow::matlabCalc);

    //Setup menu
    mpSetupMenu = menuBar()->addMenu(QString("设置(&S)"));

    //DataSave Menu
    mpDataSaveMenu = menuBar()->addMenu(QString("数据保存(&D)"));

    //About Menu
    mpAboutMenu = menuBar()->addMenu(QString("关于(&A)"));

}

void MainWindow::createToolBar()
{
    //for (int i = 0; i < 3; ++i) {
    //    LToolBar *tb = new LToolBar(QString::fromLatin1("Tool Bar %1").arg(i + 1), this);
    //    toolBars.append(tb);
    //    addToolBar(tb);
    //}

    LToolBar *tb = new LToolBar(QString::fromLatin1("Tool_Bar_1"), this);
    toolBars.append(tb);
    addToolBar(tb);

    //tb = new LToolBar(QString::fromLatin1("Tool_Bar_1"), this);
    //toolBars.append(tb);
    //addToolBar(tb);
}

void MainWindow::saveLayout()
{}

void MainWindow::loadLayout()
{}

void MainWindow::switchLayoutDirection()
{}

void MainWindow::setCalcParams()
{
    p_setparamW = new SetParamWidget();  //definition of p_setparamW must in .h
    p_setparamW->show();
}

void MainWindow::matlabCalc()
{
    p_calcW = new CalcWidget(m_pMainWidget);
    p_calcW->show();
}
