/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:39.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mainwidget.h"
#include "setparamwidget.h"
#include "calcwidget.h"

class LToolBar;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    MainWidget *m_pMainWidget = nullptr;

public slots:
    void saveLayout();
    void loadLayout();
    void switchLayoutDirection();
    void setCalcParams();
    void matlabCalc();

private:
    void createMenuBar();
    void createToolBar();

    QMenu *mpFileMenu = nullptr;
    QMenu *mpCalcMenu = nullptr;
    QMenu *mpSetupMenu = nullptr;
    QMenu *mpDataSaveMenu = nullptr;
    QMenu *mpAboutMenu = nullptr;
    QList<LToolBar*> toolBars;
    SetParamWidget *p_setparamW;
    CalcWidget *p_calcW;


signals:

};

#endif // MAINWINDOW_H
