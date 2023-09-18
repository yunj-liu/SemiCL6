/*******************************************************************
* This file was created in Chongqing in 2023-09-12 09:09:36.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/

#include "calcwidget.h"
#include <QHBoxLayout>
#include <QProgressBar>
#include <QTimer>
#include <QDir>
#include <QSettings>

//CalcWidget::CalcWidget(QWidget *parent, MainWidget *p_mainwidget)
//    : QWidget{parent}
CalcWidget::CalcWidget(MainWidget *p_mainwidget)
{
    //set handle of MainWidget
    m_pmainwidget = p_mainwidget;

    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
    setWindowTitle(QString("计算"));
    setWindowIcon(QIcon(":/imgs/chart-90.png"));

    //connect(this, SIGNAL(closeEvent(QCloseEvent*)), this, SLOT(closeEvent(QCloseEvent*)));  should not use this, overrload closeEvent function just ok

    QVBoxLayout *layout_v = new QVBoxLayout;
    layout_v->addSpacing(5);
    layout_v->addWidget(new QLabel(QString("正在进行计算，请稍后...")));  //setLayout will auto pass parent to all added in the layout
    QProgressBar *pProgressbar = new QProgressBar;
    pProgressbar->setOrientation(Qt::Horizontal);
    pProgressbar->setMinimum(0);  //Busy indication
    pProgressbar->setMaximum(0);
    layout_v->addWidget(pProgressbar);
    layout_v->addSpacing(10);

    m_pCautionLabel = new QLabel("请勿关闭窗口和程序");
    m_pPicLabel = new QLabel();
    m_pPicLabel->resize(24, 24);
    QPixmap pix(":/imgs/notifications-90.png");
    QPixmap destPix = pix.scaled(m_pPicLabel->size(), Qt::KeepAspectRatio);
    m_pPicLabel->setPixmap(destPix);

    QHBoxLayout *layout_h = new QHBoxLayout;
    layout_h->addWidget(m_pPicLabel);
    layout_h->addWidget(m_pCautionLabel);
    layout_h->addStretch(1);
    m_pPicLabel->setHidden(true);
    m_pCautionLabel->setHidden(true);

    layout_v->addLayout(layout_h);

    layout_v->addStretch(1);
    setLayout(layout_v);

    resize(530, 110);

    //params
    //lineedit1
    double dLamda = 1000;   //Laser wavelength. 0-2000 double
    //lineedit2
    double dT = 300;        //operating temperature. -200~500 double.
    //lineedit3
    double dPpump = 5;      //pumping power. 0~1000 double.
    //lineedit4
    double dDpump = 200;    //Pump spot diameter. 0~1000 double.
    //lineedit5
    double dNwell = 12;     //Number of quantum Wells. 0~50. int
    //lineedit6
    double dDwell = 6;      //Quantum well thickness. 0~20. int
    //radiobutton
    double dResonant = 1;
    double dEpitaxy = 1;
    double dQW = 1;
    double dBarrier = 1;
    double dDBR = 1;
    double dCompensation = 0;

    //read init
    QString currend_path(QDir::currentPath());
    QString sPathName = currend_path + "/option.ini";
    QSettings *m_IniFile = nullptr;
    m_IniFile = new QSettings(sPathName, QSettings::IniFormat);
    if(m_IniFile!=nullptr)  //cannot use if(!m_IniFile)
    {
        m_IniFile->beginGroup(QString("lineedit"));
        dLamda = m_IniFile->value(QString("dLamda")).toDouble();
        dT = m_IniFile->value(QString("dT")).toDouble();
        dPpump = m_IniFile->value(QString("dPpump")).toDouble();
        dDpump = m_IniFile->value(QString("dDpump")).toDouble();
        dNwell = m_IniFile->value(QString("dNwell")).toDouble();
        dDwell = m_IniFile->value(QString("dDwell")).toDouble();
        m_IniFile->endGroup();

        m_IniFile->beginGroup(QString("radiobutton"));
        dResonant = m_IniFile->value(QString("dResonant")).toDouble();
        dEpitaxy = m_IniFile->value(QString("dEpitaxy")).toDouble();
        dQW = m_IniFile->value(QString("dQW")).toDouble();
        dBarrier = m_IniFile->value(QString("dBarrier")).toDouble();
        dDBR = m_IniFile->value(QString("dDBR")).toDouble();
        dCompensation = m_IniFile->value(QString("dCompensation")).toDouble();
        m_IniFile->endGroup();
    }

    m_ArrInParams[0] = dLamda;
    m_ArrInParams[1] = dT;
    m_ArrInParams[2] = dPpump;
    m_ArrInParams[3] = dDpump;
    m_ArrInParams[4] = dNwell;
    m_ArrInParams[5] = dDwell;
    m_ArrInParams[6] = dResonant;
    m_ArrInParams[7] = dEpitaxy;
    m_ArrInParams[8] = dQW;
    m_ArrInParams[9] = dBarrier;
    m_ArrInParams[10] = dDBR;
    m_ArrInParams[11] = dCompensation;


    //worker thread
    m_thread = new CalcMatlabThread(this, &m_ArrInParams);
    connect(m_thread, &CalcMatlabThread::SendMatlabDoneInfo, this, &CalcWidget::doMatlabDone);
    connect(m_thread, &CalcMatlabThread::finished, m_thread, &CalcWidget::deleteLater);

    connect(m_thread, &CalcMatlabThread::SendMatlabDoneInfo, m_pmainwidget, &MainWidget::doMatlabDone);

    m_thread->start();

}

void CalcWidget::closeEvent(QCloseEvent *event)
{
    //qDebug() << "close event.";
    m_pPicLabel->setHidden(false);
    m_pCautionLabel->setHidden(false);
    //m_pCautionLabel->setText(QString("请勿关闭窗口和程序"));
    QTimer::singleShot(3000, m_pCautionLabel, SLOT(hide()));
    QTimer::singleShot(3000, m_pPicLabel, SLOT(hide()));
    if(!m_calcDone){
        event->ignore();
    }
}

void CalcWidget::doMatlabDone(const QString info, const FigureData figure_datatablemap)
{
    qDebug() << info;
    m_calcDone = true;
    close();
    close();
}
