/*******************************************************************
* This file was created in Chongqing in 2023-09-11 09:05:53.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/

#include "setparamwidget.h"
#include <QGroupBox>
#include <QHBoxLayout>
#include <QPushButton>
#include <QLabel>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QButtonGroup>
#include <QDir>
#include <QSettings>
#include <QFile>

SetParamWidget::SetParamWidget(QWidget *parent, MainWidget *pMainWidget)
    : QWidget{parent}
{ 
    setWindowModality(Qt::ApplicationModal);
    setWindowFlags(windowFlags() & ~Qt::WindowMinMaxButtonsHint);
    setWindowTitle(QString("设置运算参数"));
    setWindowIcon(QIcon(":/imgs/formula-color-fx-96.png"));
    m_pMainWidget = pMainWidget;

    //Row 1
    QGroupBox *topinputGroupBox1 = new QGroupBox(QString("输入参数1"));
    QVBoxLayout *layout_g1v1 = new QVBoxLayout;
    layout_g1v1->addWidget(new QLabel(QString("激光波长")));
    layout_g1v1->addWidget(new QLabel(QString("工作温度")));
    QVBoxLayout *layout_g1v2 = new QVBoxLayout;
    lineedit1 = new QLineEdit;
    lineedit2 = new QLineEdit;
    layout_g1v2->addWidget(lineedit1);
    layout_g1v2->addWidget(lineedit2);
    QVBoxLayout *layout_g1v3 = new QVBoxLayout;
    layout_g1v3->addWidget(new QLabel(QString("nm(850~1200)")));
    layout_g1v3->addWidget(new QLabel(QString("K(250~350)")));
    QHBoxLayout *layout_g1h = new QHBoxLayout;
    layout_g1h->addLayout(layout_g1v1);
    layout_g1h->addLayout(layout_g1v2);
    layout_g1h->addLayout(layout_g1v3);
    topinputGroupBox1->setLayout(layout_g1h);

    QGroupBox *topinputGroupBox2 = new QGroupBox(QString("输入参数2"));
    QVBoxLayout *layout_g2v1 = new QVBoxLayout;
    layout_g2v1->addWidget(new QLabel(QString("泵浦功率")), 0, Qt::AlignRight);  //Align Right
    layout_g2v1->addWidget(new QLabel(QString("泵浦光斑直径")), 0, Qt::AlignRight);
    QVBoxLayout *layout_g2v2 = new QVBoxLayout;
    lineedit3 = new QLineEdit;
    lineedit4 = new QLineEdit;
    layout_g2v2->addWidget(lineedit3);
    layout_g2v2->addWidget(lineedit4);
    QVBoxLayout *layout_g2v3 = new QVBoxLayout;
    layout_g2v3->addWidget(new QLabel(QString("W(0~100)")));
    layout_g2v3->addWidget(new QLabel(QString("um(100~500)")));
    QHBoxLayout *layout_g2h = new QHBoxLayout;
    layout_g2h->addLayout(layout_g2v1);
    layout_g2h->addLayout(layout_g2v2);
    layout_g2h->addLayout(layout_g2v3);
    topinputGroupBox2->setLayout(layout_g2h);

    QHBoxLayout *g1g2H1 = new QHBoxLayout;
    g1g2H1->addWidget(topinputGroupBox1);
    g1g2H1->addWidget(topinputGroupBox2);

    //Row 2
    QGroupBox *topinputGroupBox3 = new QGroupBox(QString("输入参数3"));
    QVBoxLayout *layout_g3v1 = new QVBoxLayout;
    layout_g3v1->addWidget(new QLabel(QString("量子阱数目")));
    layout_g3v1->addWidget(new QLabel(QString("量子阱厚度")));
    QVBoxLayout *layout_g3v2 = new QVBoxLayout;
    lineedit5 = new QLineEdit;
    lineedit6 = new QLineEdit;
    layout_g3v2->addWidget(lineedit5);
    layout_g3v2->addWidget(lineedit6);
    QVBoxLayout *layout_g3v3 = new QVBoxLayout;
    layout_g3v3->addWidget(new QLabel(QString("个(5~20)")));
    layout_g3v3->addWidget(new QLabel(QString("nm(5~20)")));
    QHBoxLayout *layout_g3h = new QHBoxLayout;
    layout_g3h->addLayout(layout_g3v1);
    layout_g3h->addLayout(layout_g3v2);
    layout_g3h->addLayout(layout_g3v3);
    topinputGroupBox3->setLayout(layout_g3h);

    QGroupBox *topinputGroupBox4 = new QGroupBox(QString("微腔结构"));
    radiog41 = new QRadioButton(QString("谐振型"));
    radiog42 = new QRadioButton(QString("反谐振型"));
    radiog43 = new QRadioButton(QString("中间型"));
    radiog41->setChecked(true);
    btnGroup4 = new QButtonGroup;  //btnGroup not add into layout, just for fetch checkedId
    btnGroup4->addButton(radiog41, 1);
    btnGroup4->addButton(radiog42, 2);
    btnGroup4->addButton(radiog43, 3);
    QHBoxLayout *layout_g4h = new QHBoxLayout;
    layout_g4h->addWidget(radiog41);
    layout_g4h->addWidget(radiog42);
    layout_g4h->addWidget(radiog43);
    //layout_g4h->addStretch(1);
    topinputGroupBox4->setLayout(layout_g4h);

    QHBoxLayout *g3g4H2 = new QHBoxLayout;
    g3g4H2->addWidget(topinputGroupBox3, 1);
    g3g4H2->addWidget(topinputGroupBox4, 1);

    //row3
    QGroupBox *topinputGroupBox5 = new QGroupBox(QString("外延生长顺序"));
    radiog51 = new QRadioButton(QString("正序"));
    radiog52 = new QRadioButton(QString("逆序"));
    radiog51->setChecked(true);
    btnGroup5 = new QButtonGroup;  //btnGroup not add into layout, just for fetch checkedId
    btnGroup5->addButton(radiog51, 1);
    btnGroup5->addButton(radiog52, 2);
    QHBoxLayout *layout_g5h = new QHBoxLayout;
    layout_g5h->addWidget(radiog51);
    layout_g5h->addWidget(radiog52);
    topinputGroupBox5->setLayout(layout_g5h);

    QGroupBox *topinputGroupBox6 = new QGroupBox(QString("量子阱材料"));
    radiog61 = new QRadioButton(QString("InGaAs"));
    radiog62 = new QRadioButton(QString("AlGaAs"));
    radiog63 = new QRadioButton(QString("GaAsP"));
    radiog61->setChecked(true);
    btnGroup6 = new QButtonGroup;  //btnGroup not add into layout, just for fetch checkedId
    btnGroup6->addButton(radiog61, 1);
    btnGroup6->addButton(radiog62, 2);
    btnGroup6->addButton(radiog63, 3);
    radiog62->setCheckable(false);
    radiog63->setCheckable(false);

    QHBoxLayout *layout_g6h = new QHBoxLayout;
    layout_g6h->addWidget(radiog61);
    layout_g6h->addWidget(radiog62);
    layout_g6h->addWidget(radiog63);
    topinputGroupBox6->setLayout(layout_g6h);
    QHBoxLayout *g5g6H3 = new QHBoxLayout;
    g5g6H3->addWidget(topinputGroupBox5);
    g5g6H3->addWidget(topinputGroupBox6);

    //row4
    QGroupBox *topinputGroupBox7 = new QGroupBox(QString("势垒材料"));
    radiog71 = new QRadioButton(QString("GaAs"));
    radiog72 = new QRadioButton(QString("AlGaAs"));
    radiog73 = new QRadioButton(QString("GaAsP"));
    radiog71->setChecked(true);
    btnGroup7 = new QButtonGroup;  //btnGroup not add into layout, just for fetch checkedId
    btnGroup7->addButton(radiog71, 1);
    btnGroup7->addButton(radiog72, 2);
    btnGroup7->addButton(radiog73, 3);
    QHBoxLayout *layout_g7h = new QHBoxLayout;
    layout_g7h->addWidget(radiog71);
    layout_g7h->addWidget(radiog72);
    layout_g7h->addWidget(radiog73);
    topinputGroupBox7->setLayout(layout_g7h);

    QGroupBox *topinputGroupBox8 = new QGroupBox(QString("DBR材料"));
    radiog81 = new QRadioButton(QString("GaAs/AlAs"));
    radiog82 = new QRadioButton(QString("GaAs/Al0.9GaAs"));
    radiog83 = new QRadioButton(QString("Al0.1GaAs/Al0.9GaAs"));
    radiog81->setChecked(true);
    btnGroup8 = new QButtonGroup;  //btnGroup not add into layout, just for fetch checkedId
    btnGroup8->addButton(radiog81, 1);
    btnGroup8->addButton(radiog82, 2);
    btnGroup8->addButton(radiog83, 3);
    QHBoxLayout *layout_g8h = new QHBoxLayout;
    layout_g8h->addWidget(radiog81);
    layout_g8h->addWidget(radiog82);
    layout_g8h->addWidget(radiog83);
    topinputGroupBox8->setLayout(layout_g8h);
    QHBoxLayout *g7g8H4 = new QHBoxLayout;
    g7g8H4->addWidget(topinputGroupBox7);
    g7g8H4->addWidget(topinputGroupBox8);

    //row5
    QGroupBox *topinputGroupBox9 = new QGroupBox(QString("应力补偿层材料"));
    radiog91 = new QRadioButton(QString("不选"));
    radiog92 = new QRadioButton(QString("选"));
    radiog91->setChecked(true);
    btnGroup9 = new QButtonGroup;  //btnGroup not add into layout, just for fetch checkedId
    btnGroup9->addButton(radiog91, 0);
    btnGroup9->addButton(radiog92, 1);
    QHBoxLayout *layout_g9h = new QHBoxLayout;
    layout_g9h->addWidget(radiog91);
    layout_g9h->addWidget(radiog92);
    topinputGroupBox9->setLayout(layout_g9h);

    QHBoxLayout *g9H5 = new QHBoxLayout;
    g9H5->addWidget(topinputGroupBox9,1);
    g9H5->addStretch(1);



    //QDialogButtonBox
    QDialogButtonBox *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok
                                     | QDialogButtonBox::Cancel);
    buttonBox->button(QDialogButtonBox::Ok)->setText(QString("确定"));
    buttonBox->button(QDialogButtonBox::Cancel)->setText(QString("取消"));

    QVBoxLayout *mainLayout = new QVBoxLayout;
    mainLayout->addLayout(g1g2H1);
    mainLayout->addLayout(g3g4H2);
    mainLayout->addLayout(g5g6H3);
    mainLayout->addLayout(g7g8H4);
    mainLayout->addLayout(g9H5);
    mainLayout->addWidget(buttonBox);

    setLayout(mainLayout);

    // read ini
    QString currend_path(QDir::currentPath());
    QString sPathName = currend_path + "/option.ini";
    QFile file;
    file.setFileName(sPathName);
    if(file.exists()){
        QSettings *m_IniFile = new QSettings(sPathName, QSettings::IniFormat);  //cant use m_IniFile!=nullptr judge file exist or not
        m_IniFile->beginGroup(QString("lineedit"));
        lineedit1->setText(m_IniFile->value(QString("dLamda")).toString());
        lineedit2->setText(m_IniFile->value(QString("dT")).toString());
        lineedit3->setText(m_IniFile->value(QString("dPpump")).toString());
        lineedit4->setText(m_IniFile->value(QString("dDpump")).toString());
        lineedit5->setText(m_IniFile->value(QString("dNwell")).toString());
        lineedit6->setText(m_IniFile->value(QString("dDwell")).toString());
        m_IniFile->endGroup();

        int radioid;
        m_IniFile->beginGroup(QString("radiobutton"));
        radioid = m_IniFile->value(QString("dResonant")).toInt();
        btnGroup4->button(radioid)->setChecked(true);
        radioid = m_IniFile->value(QString("dEpitaxy")).toInt();
        btnGroup5->button(radioid)->setChecked(true);
        radioid = m_IniFile->value(QString("dQW")).toInt();
        btnGroup6->button(radioid)->setChecked(true);
        radioid = m_IniFile->value(QString("dBarrier")).toInt();
        btnGroup7->button(radioid)->setChecked(true);
        radioid = m_IniFile->value(QString("dDBR")).toInt();
        btnGroup8->button(radioid)->setChecked(true);
        radioid = m_IniFile->value(QString("dCompensation")).toInt();
        btnGroup9->button(radioid)->setChecked(true);
        m_IniFile->endGroup();
    }
    else{
        lineedit1->setText(QString("1000"));
        lineedit2->setText(QString("300"));
        lineedit3->setText(QString("5"));
        lineedit4->setText(QString("200"));
        lineedit5->setText(QString("12"));
        lineedit6->setText(QString("6"));
        btnGroup4->button(1)->setChecked(true);
        btnGroup5->button(1)->setChecked(true);
        btnGroup6->button(1)->setChecked(true);
        btnGroup7->button(1)->setChecked(true);
        btnGroup8->button(1)->setChecked(true);
        btnGroup9->button(0)->setChecked(true);
    }

    connect(buttonBox, SIGNAL(accepted()), this, SLOT(setParamOk()));
    connect(buttonBox, SIGNAL(rejected()), this, SLOT(setParamCancel()));

}

void SetParamWidget::setParamOk()
{
    //qDebug() << "test ok";
    /*
    lineedit3->setText(QString("abcde"));
    lineedit3->setFocus();
    lineedit3->selectAll();
    qDebug() << btnGroup4->checkedId();
    qDebug() << btnGroup5->checkedId();
    qDebug() << btnGroup6->checkedId();
    qDebug() << btnGroup7->checkedId();
    qDebug() << btnGroup8->checkedId();
    qDebug() << btnGroup9->checkedId();
    qDebug() << lineedit1->text().toDouble();
    qDebug() << lineedit2->text().toDouble();
    qDebug() << lineedit3->text().toDouble();
    qDebug() << lineedit4->text().toDouble();
    qDebug() << lineedit5->text().toDouble();
    qDebug() << lineedit6->text().toDouble();
    */
    bool valid = false;
    //lineedit1
    double dLamda = lineedit1->text().toDouble(&valid);  //Laser wavelength. 850-1200 double
    if(!valid){
        lineedit1->setFocus();
        lineedit1->selectAll();
        return;
    }
    if(dLamda < 850){
        lineedit1->setFocus();
        lineedit1->selectAll();
        return;
    }
    if(dLamda > 1200){
        lineedit1->setFocus();
        lineedit1->selectAll();
        return;
    }

    //lineedit2
    double dT = lineedit2->text().toDouble(&valid);  //operating temperature. 250~350 double.
    if(!valid){
        lineedit2->setFocus();
        lineedit2->selectAll();
        return;
    }
    if(dT < 250){
        lineedit2->setFocus();
        lineedit2->selectAll();
        return;
    }
    if(dT > 350){
        lineedit2->setFocus();
        lineedit2->selectAll();
        return;
    }

    //lineedit3
    double dPpump = lineedit3->text().toDouble(&valid);  //pumping power. 0~100 double.
    if(!valid){
        lineedit3->setFocus();
        lineedit3->selectAll();
        return;
    }
    if(dPpump < 0){
        lineedit3->setFocus();
        lineedit3->selectAll();
        return;
    }
    if(dPpump > 100){
        lineedit3->setFocus();
        lineedit3->selectAll();
        return;
    }

    //lineedit4
    double dDpump = lineedit4->text().toDouble(&valid);  //Pump spot diameter. 100~500 double.
    if(!valid){
        lineedit4->setFocus();
        lineedit4->selectAll();
        return;
    }
    if(dDpump < 100){
        lineedit4->setFocus();
        lineedit4->selectAll();
        return;
    }
    if(dDpump > 500){
        lineedit4->setFocus();
        lineedit4->selectAll();
        return;
    }

    //lineedit5
    double dNwell = (double)lineedit5->text().toInt(&valid);  //Number of quantum Wells. 5~20. int
    if(!valid){
        lineedit5->setFocus();
        lineedit5->selectAll();
        return;
    }
    if(dNwell < 5){
        lineedit5->setFocus();
        lineedit5->selectAll();
        return;
    }
    if(dNwell > 20){
        lineedit5->setFocus();
        lineedit5->selectAll();
        return;
    }

    //lineedit6
    double dDwell = (double)lineedit6->text().toInt(&valid);  //Quantum well thickness. 5~20. int
    if(!valid){
        lineedit6->setFocus();
        lineedit6->selectAll();
        return;
    }
    if(dDwell < 5){
        lineedit6->setFocus();
        lineedit6->selectAll();
        return;
    }
    if(dDwell > 20){
        lineedit6->setFocus();
        lineedit6->selectAll();
        return;
    }

    double dResonant = (double)btnGroup4->checkedId();
    double dEpitaxy = (double)btnGroup5->checkedId();
    double dQW = (double)btnGroup6->checkedId();
    double dBarrier = (double)btnGroup7->checkedId();
    double dDBR = (double)btnGroup8->checkedId();
    double dCompensation = (double)btnGroup9->checkedId();

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

    //fresh mainwidget
    m_pMainWidget->refershChartThemes();

    this->close();
}

void SetParamWidget::setParamCancel()
{
    //qDebug() << "test cancel";
    this->close();
}
