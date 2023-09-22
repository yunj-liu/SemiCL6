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
#include "ltoolbar1.h"
#include <QDir>
#include <QSettings>
#include <QFile>
#include <QActionGroup>
#include <QFileDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow{parent}
{
    //qApp->setApplicationDisplayName(tr("半导体激光器芯片设计软件 SemiCL V1.0 - NCAMCQ"));  //instead of setWindowTitle
    setObjectName("MainWindow");
    setWindowTitle("半导体激光器芯片设计软件 SemiCL V1.0 - NCAMCQ");

    createMenuBar();
    createToolBar();

    //CentralWidget
    m_pMainWidget = new MainWidget(this, m_ct, m_ao);
    setCentralWidget(m_pMainWidget);

    statusBar()->showMessage(QString("已启动."), 3000);

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
    mpCalcMenu->addAction(QIcon(":/imgs/sort-green-right-90.png"), QString("计算"), this, &MainWindow::matlabCalc);
    mpCalcMenu->addSeparator();
    mpCalcMenu->addAction(QIcon(":/imgs/update-left-rotation-64.png"), QString("参数恢复默认值"), this, &MainWindow::resetCalcParams);

    //Setup menu
    mpSetupMenu = menuBar()->addMenu(QString("设置(&S)"));
    generateSetupMenu(mpSetupMenu);

    //DataSave Menu
    mpDataSaveMenu = menuBar()->addMenu(QString("数据保存(&D)"));
    mpDataSaveMenu->addAction(QIcon(":/imgs/ios-save-60.png"), QString("图表数据保存..."), this, &MainWindow::figuresSave);
    mpDataSaveMenu->addAction(QIcon(":/imgs/ios-save-as-60.png"), QString("图表数据另存为..."), this, &MainWindow::figuresSaveAs);

    //Report menu
    mpReportMenu = menuBar()->addMenu(QString("设计报告(&R)"));
    mpReportMenu->addAction(QIcon(":/imgs/chip-60.png"), QString("芯片外延结构"), this, &MainWindow::epitaxyStruct);
    mpReportMenu->addAction(QIcon(":/imgs/refraction-48.png"), QString("外延材料折射率"), this, &MainWindow::refractiveIndex);

    //About Menu
    mpAboutMenu = menuBar()->addMenu(QString("关于(&A)"));
    mpAboutMenu->addAction(QIcon(":/imgs/blue-about-60.png"), QString("关于..."), this, &MainWindow::about);

}

void MainWindow::refractiveIndex()
{
    p_refracIdxW = new RefracIdxWidget();
    p_refracIdxW->show();

}

void MainWindow::epitaxyStruct()
{
    p_epStructW = new EpStructWidget();
    p_epStructW->show();
}

void MainWindow::about()
{
    p_aboutW = new AboutWidget();
    p_aboutW->show();
}

void MainWindow::figuresSave()
{
    if(m_figureSavePathName.isEmpty()){
        figuresSaveAs();
    }
    else{
        FigureData& fd = m_pMainWidget->getFigureData();
        qDebug()<< m_figureSavePathName;
        for(int i(1); i<=7; i++){
            CommonControl::saveDataTableToCsvFile(m_figureSavePathName, QString("figure")+QString::number(i), fd[QString("figure")+QString::number(i)]);
        }
        statusBar()->showMessage(QString("数据已保存. 图表1-7数据已保存至")+m_figureSavePathName, 5000);
    }

}

void MainWindow::figuresSaveAs()
{
    statusBar()->showMessage(QString("请选择要保存图表1-7数据文件的位置"));

    //QString fileName = QFileDialog::getSaveFileName(this, QString("Save File"), QDir::homePath());
    QFileDialog *fileDialog;
    if(m_figureSavePathName.isEmpty())
        fileDialog = new QFileDialog(this, QString("请选择保存数据文件的位置"), QDir::homePath());
    else
        fileDialog = new QFileDialog(this, QString("请选择保存数据文件的位置"), m_figureSavePathName);
    fileDialog->setFileMode(QFileDialog::Directory);

    /*fileDialog->exec();  //if use this way,then if clcik cancel button or close dialog also still get selectedFiles, get the path
    QStringList selectDir = fileDialog->selectedFiles();
    if (selectDir.size()>0){
        qDebug() << selectDir.size();
        qDebug() << "Dir Path:" << selectDir.at(0);
    }*/

    QString sPathName = fileDialog->getExistingDirectory();  // if clcik cacel button or close dialog, will get the empty string ""
    //qDebug() << sPath;  //the string of sPath has no end slash

    if(!sPathName.isEmpty())
    {
        //qDebug() << "not empty";
        FigureData& fd = m_pMainWidget->getFigureData();  //get the FigureData
        if(!sPathName.endsWith('/')){
            sPathName += "/";
        }
        m_figureSavePathName = sPathName;  //if sPathName is not empty, save path in m_figureSavePathName
        for(int i(1); i<=7; i++){
            CommonControl::saveDataTableToCsvFile(sPathName, QString("figure")+QString::number(i), fd[QString("figure")+QString::number(i)]);
        }
        statusBar()->showMessage(QString("数据已保存. 图表1-7数据已保存至")+sPathName, 3000);
    }
    else{
        statusBar()->showMessage(QString("位置路径为空."), 3000);
    }
}

void MainWindow::generateSetupMenu(QMenu *pSetupMenu)
{
    // read ini
    QString currend_path(QDir::currentPath());
    QString sPathName = currend_path + "/option.ini";
    QFile file;
    file.setFileName(sPathName);
    if(file.exists()){
        QSettings *m_IniFile = new QSettings(sPathName, QSettings::IniFormat);
        m_ct = (QChart::ChartTheme)m_IniFile->value(QString("/theme/themevalue")).toInt();
        m_ao = (QChart::AnimationOption)m_IniFile->value(QString("/animation/animationvalue")).toInt();
    }


    //QMenu *testmenu = new QMenu(QString("test1"), this);
    //pSetupMenu->addMenu(testmenu);

    //theme action group
    m_themeActions = new QActionGroup(this);
    m_themeActions->setExclusive(true);

    m_lightAction = new QAction(QString("Light"), this);
    m_lightAction->setCheckable(true);
    connect(m_lightAction, &QAction::triggered, this, &MainWindow::chooseTheme);

    m_blueCeruleanAction = new QAction(QString("Blue Cerulean"), this);
    m_blueCeruleanAction->setCheckable(true);
    connect(m_blueCeruleanAction, &QAction::triggered, this, &MainWindow::chooseTheme);

    m_darkAction = new QAction(QString("Dark"), this);
    m_darkAction->setCheckable(true);
    connect(m_darkAction, &QAction::triggered, this, &MainWindow::chooseTheme);

    m_brownSandAction = new QAction(QString("Brown Sand"), this);
    m_brownSandAction->setCheckable(true);
    connect(m_brownSandAction, &QAction::triggered, this, &MainWindow::chooseTheme);

    m_blueNCSAction = new QAction(QString("Blue NCS"), this);
    m_blueNCSAction->setCheckable(true);
    connect(m_blueNCSAction, &QAction::triggered, this, &MainWindow::chooseTheme);

    m_highContrastAction = new QAction(QString("High Contrast"), this);
    m_highContrastAction->setCheckable(true);
    connect(m_highContrastAction, &QAction::triggered, this, &MainWindow::chooseTheme);

    m_blueIcyAction = new QAction(QString("Blue Icy"), this);
    m_blueIcyAction->setCheckable(true);
    connect(m_blueIcyAction, &QAction::triggered, this, &MainWindow::chooseTheme);

    m_contrastAction = new QAction(QString("Contrast"), this);
    m_contrastAction->setCheckable(true);
    connect(m_contrastAction, &QAction::triggered, this, &MainWindow::chooseTheme);

    if(m_ct == QChart::ChartThemeLight)
        m_lightAction->setChecked(true);
    else if(m_ct == QChart::ChartThemeBlueCerulean)
        m_blueCeruleanAction->setChecked(true);
    else if(m_ct == QChart::ChartThemeDark)
        m_darkAction->setChecked(true);
    else if(m_ct == QChart::ChartThemeBrownSand)
        m_brownSandAction->setChecked(true);
    else if(m_ct == QChart::ChartThemeBlueNcs)
        m_blueNCSAction->setChecked(true);
    else if(m_ct == QChart::ChartThemeHighContrast)
        m_highContrastAction->setChecked(true);
    else if(m_ct == QChart::ChartThemeBlueIcy)
        m_blueIcyAction->setChecked(true);
    else if(m_ct == QChart::ChartThemeQt)
        m_contrastAction->setChecked(true);

    m_themeActions->addAction(m_lightAction);
    m_themeActions->addAction(m_blueCeruleanAction);
    m_themeActions->addAction(m_darkAction);
    m_themeActions->addAction(m_brownSandAction);
    m_themeActions->addAction(m_blueNCSAction);
    m_themeActions->addAction(m_highContrastAction);
    m_themeActions->addAction(m_blueIcyAction);
    m_themeActions->addAction(m_contrastAction);

    pSetupMenu->addActions(m_themeActions->actions());
    pSetupMenu->addSeparator();

    //theme action group
    m_animationActions = new QActionGroup(this);
    m_animationActions->setExclusive(true);

    m_NoAnimationAction = new QAction(QString("No Animations"), this);
    m_NoAnimationAction->setCheckable(true);
    connect(m_NoAnimationAction, &QAction::triggered, this, &MainWindow::chooseAnimations);

    m_GridAxisAnimationsAction = new QAction(QString("GridAxis Animations"), this);
    m_GridAxisAnimationsAction->setCheckable(true);
    connect(m_GridAxisAnimationsAction, &QAction::triggered, this, &MainWindow::chooseAnimations);

    m_SeriesAnimationsAction = new QAction(QString("Series Animations"), this);
    m_SeriesAnimationsAction->setCheckable(true);
    connect(m_SeriesAnimationsAction, &QAction::triggered, this, &MainWindow::chooseAnimations);

    m_AllAnimationsAction = new QAction(QString("All Animations"), this);
    m_AllAnimationsAction->setCheckable(true);
    connect(m_AllAnimationsAction, &QAction::triggered, this, &MainWindow::chooseAnimations);

    if(m_ao == QChart::NoAnimation)
        m_NoAnimationAction->setChecked(true);
    else if(m_ao == QChart::GridAxisAnimations)
        m_GridAxisAnimationsAction->setChecked(true);
    else if(m_ao == QChart::SeriesAnimations)
        m_SeriesAnimationsAction->setChecked(true);
    else if(m_ao == QChart::AllAnimations)
        m_AllAnimationsAction->setChecked(true);

    m_animationActions->addAction(m_NoAnimationAction);
    m_animationActions->addAction(m_GridAxisAnimationsAction);
    m_animationActions->addAction(m_SeriesAnimationsAction);
    m_animationActions->addAction(m_AllAnimationsAction);

    pSetupMenu->addActions(m_animationActions->actions());


}

void MainWindow::chooseTheme()
{
    if(m_lightAction->isChecked())
        m_ct = QChart::ChartThemeLight;  // value 0
    else if(m_blueCeruleanAction->isChecked())
        m_ct = QChart::ChartThemeBlueCerulean;
    else if(m_darkAction->isChecked())
        m_ct = QChart::ChartThemeDark;
    else if(m_brownSandAction->isChecked())
        m_ct = QChart::ChartThemeBrownSand;
    else if(m_blueNCSAction->isChecked())
        m_ct = QChart::ChartThemeBlueNcs;
    else if(m_highContrastAction->isChecked())
        m_ct = QChart::ChartThemeHighContrast;
    else if(m_blueIcyAction->isChecked())
        m_ct = QChart::ChartThemeBlueIcy;
    else if(m_contrastAction->isChecked())
        m_ct = QChart::ChartThemeQt;

    //write ini
    QString currend_path(QDir::currentPath());
    QString sPathName = currend_path + "/option.ini";
    QSettings *m_IniFile = new QSettings(sPathName, QSettings::IniFormat);
    m_IniFile->setValue(QString("/theme/themevalue"), m_ct);

    //set active (just refresh)
    m_pMainWidget->setActiveWithIndex(m_pMainWidget->getListviewCurrentIndex(), m_ct, m_ao);
}

void MainWindow::nextFigure()
{
    int index = 0;
    index = m_pMainWidget->getListviewCurrentIndex();
    if(index < 7)
    {
        index++;
        m_pMainWidget->setActiveWithIndex(index, m_ct, m_ao);
    }

}

void MainWindow::upFigure()
{
    int index = 0;
    index = m_pMainWidget->getListviewCurrentIndex();
    if(index > 0)
    {
        index--;
        m_pMainWidget->setActiveWithIndex(index, m_ct, m_ao);
    }
}

void MainWindow::chooseAnimations()
{
    if(m_NoAnimationAction->isChecked())
        m_ao = QChart::NoAnimation;  // value 0
    else if(m_GridAxisAnimationsAction->isChecked())
        m_ao = QChart::GridAxisAnimations;
    else if(m_SeriesAnimationsAction->isChecked())
        m_ao = QChart::SeriesAnimations;
    else if(m_AllAnimationsAction->isChecked())
        m_ao = QChart::AllAnimations;

    //write ini
    QString currend_path(QDir::currentPath());
    QString sPathName = currend_path + "/option.ini";
    QSettings *m_IniFile = new QSettings(sPathName, QSettings::IniFormat);
    m_IniFile->setValue(QString("/animation/animationvalue"), m_ao);

    //set active (just refresh)
    m_pMainWidget->setActiveWithIndex(m_pMainWidget->getListviewCurrentIndex(), m_ct, m_ao);
}

void MainWindow::createToolBar()
{
    //for (int i = 0; i < 3; ++i) {
    //    LToolBar *tb = new LToolBar(QString::fromLatin1("Tool Bar %1").arg(i + 1), this);
    //    toolBars.append(tb);
    //    addToolBar(tb);
    //}

    LToolBar1 *tb1 = new LToolBar1(QString::fromLatin1("Tool_Bar_1"), this);  //LToolBar，l indeicate lyj
    toolBars.append(tb1);
    addToolBar(tb1);

}

void MainWindow::saveLayout()
{}

void MainWindow::loadLayout()
{}

void MainWindow::switchLayoutDirection()
{}

void MainWindow::setCalcParams()
{
    p_setparamW = new SetParamWidget(nullptr, m_pMainWidget);  //definition of p_setparamW must in .h
    p_setparamW->show();
}

void MainWindow::matlabCalc()
{
    p_calcW = new CalcWidget(m_pMainWidget);
    p_calcW->show();
}

void MainWindow::resetCalcParams()
{
    //lineedit1
    double dLamda = 1000;  //Laser wavelength. 850-1200 double

    //lineedit2
    double dT = 300;  //operating temperature. 250~350 double.

    //lineedit3
    double dPpump = 5;  //pumping power. 0~100 double.

    //lineedit4
    double dDpump = 200;  //Pump spot diameter. 100~500 double.

    //lineedit5
    double dNwell = 12;  //Number of quantum Wells. 5~20. int

    //lineedit6
    double dDwell = 6;  //Quantum well thickness. 5~20. int

    double dResonant = 1;
    double dEpitaxy = 1;
    double dQW = 1;
    double dBarrier = 1;
    double dDBR = 1;
    double dCompensation = 0;

    //write ini
    QString currend_path(QDir::currentPath());
    QString sPathName = currend_path + "/option.ini";
    QSettings *m_IniFile = new QSettings(sPathName, QSettings::IniFormat);
    m_IniFile->beginGroup(QString("lineedit"));
    m_IniFile->setValue(QString("dLamda"), dLamda);  //dont use QString::number(dLamda), it will Truncation accuracy
    m_IniFile->setValue(QString("dT"), dT);
    m_IniFile->setValue(QString("dPpump"), dPpump);
    m_IniFile->setValue(QString("dDpump"), dDpump);
    m_IniFile->setValue(QString("dNwell"), dNwell);
    m_IniFile->setValue(QString("dDwell"), dDwell);
    m_IniFile->endGroup();

    m_IniFile->beginGroup(QString("radiobutton"));
    m_IniFile->setValue(QString("dResonant"), QString::number(dResonant));
    m_IniFile->setValue(QString("dEpitaxy"), QString::number(dEpitaxy));
    m_IniFile->setValue(QString("dQW"), QString::number(dQW));
    m_IniFile->setValue(QString("dBarrier"), QString::number(dBarrier));
    m_IniFile->setValue(QString("dDBR"), QString::number(dDBR));
    m_IniFile->setValue(QString("dCompensation"), QString::number(dCompensation));
    m_IniFile->endGroup();

    // read csv
    FigureData datatableMap;
    datatableMap = CommonControl::getFigureDataHashMapFromCsvFile(QString("/resetdata/"), 7);
    //for(int i(1); i<=7; i++)
    //    qDebug() << datatableMap["figure"+QString::number(i)].count();

    //write csv
    CommonControl::saveFigureDataHashMapToCsvFile(QString("/projdata/"), 7, datatableMap);

    //refresh
    m_pMainWidget->refershChartThemes();
}
