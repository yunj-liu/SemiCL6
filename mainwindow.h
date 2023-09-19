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

class LToolBar1;

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
    void resetCalcParams();
    void chooseTheme();
    void chooseAnimations();
    void nextFigure();
    void upFigure();

private:
    void createMenuBar();
    void createToolBar();
    void generateSetupMenu(QMenu *pSetupMenu=nullptr);

    QMenu *mpFileMenu = nullptr;
    QMenu *mpCalcMenu = nullptr;
    QMenu *mpSetupMenu = nullptr;
    QMenu *mpDataSaveMenu = nullptr;
    QMenu *mpAboutMenu = nullptr;
    QList<LToolBar1*> toolBars;
    SetParamWidget *p_setparamW;
    CalcWidget *p_calcW;

    QActionGroup *m_themeActions = nullptr;
    QAction *m_lightAction = nullptr;
    QAction *m_blueCeruleanAction = nullptr;
    QAction *m_darkAction = nullptr;
    QAction *m_brownSandAction = nullptr;
    QAction *m_blueNCSAction = nullptr;
    QAction *m_highContrastAction = nullptr;
    QAction *m_blueIcyAction = nullptr;
    QAction *m_contrastAction = nullptr;

    QChart::ChartTheme m_ct = QChart::ChartThemeLight;

    QActionGroup *m_animationActions = nullptr;
    QAction *m_NoAnimationAction = nullptr;
    QAction *m_GridAxisAnimationsAction = nullptr;
    QAction *m_SeriesAnimationsAction = nullptr;
    QAction *m_AllAnimationsAction = nullptr;

    QChart::AnimationOption m_ao = QChart::NoAnimation;


signals:

};

#endif // MAINWINDOW_H
