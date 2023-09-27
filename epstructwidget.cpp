#include "epstructwidget.h"
#include <QLayout>
#include <QHeaderView>

EpStructWidget::EpStructWidget(DataTable *p_dt, QWidget *parent)
    : QMainWindow{parent}
    , m_pdt(p_dt)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(QString("芯片外延结构"));
    setWindowIcon(QIcon(":/imgs/chip-60.png"));
    setWindowFlags(Qt::Dialog);
    //this->layout()->setSizeConstraint(QLayout::SetFixedSize);
    layout()->setSizeConstraint(QLayout::SetFixedSize);  //both ok.

    int rows = 16;
    int cols = 4;
    m_pTableW = new QTableWidget(rows, cols, this);
    m_pTableW->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    for (int c = 0; c < cols; ++c) {
        QString character(QChar('A' + c));
        m_pTableW->setHorizontalHeaderItem(c, new QTableWidgetItem(character));  //QTableWidget & QTableWidgetItem
    }
    m_pTableW->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //stretch, resizeToContents
    for (int c = 0; c < cols; ++c) {
        m_pTableW->horizontalHeader()->setSectionResizeMode(c, QHeaderView::ResizeToContents);
    }
    m_pTableW->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //all rows set
    for (int r = 0; r < rows; ++r) {
        m_pTableW->verticalHeader()->setSectionResizeMode(r, QHeaderView::ResizeToContents);
    }

    setCentralWidget(m_pTableW);
    setupContents();
    m_pTableW->update();

    statusBar();
}

void EpStructWidget::setupContents()
{
    QBrush titleBackground(Qt::lightGray);
    QFont titleFont = m_pTableW->font();
    titleFont.setBold(true);
    titleFont.setPixelSize(40);
    titleFont.setFamily("Times New Roman");

    QFont contentFont = m_pTableW->font();
    contentFont.setPixelSize(25);
    contentFont.setFamily("Cambria");

    //column 0 header
    m_pTableW->setItem(0, 0, new QTableWidgetItem("  Material  "));
    m_pTableW->item(0, 0)->setBackground(titleBackground);
    m_pTableW->item(0, 0)->setToolTip("外延材料");
    m_pTableW->item(0, 0)->setFont(titleFont);
    m_pTableW->item(0, 0)->setTextAlignment(Qt::AlignCenter);

    //column 1 header
    m_pTableW->setItem(0, 1, new QTableWidgetItem("  Thickness/nm  "));
    m_pTableW->item(0, 1)->setBackground(titleBackground);
    m_pTableW->item(0, 1)->setToolTip("厚度");
    m_pTableW->item(0, 1)->setFont(titleFont);
    m_pTableW->item(0, 1)->setTextAlignment(Qt::AlignCenter);

    //column 2 header
    m_pTableW->setItem(0, 2, new QTableWidgetItem("  Layer  "));
    m_pTableW->item(0, 2)->setBackground(titleBackground);
    m_pTableW->item(0, 2)->setToolTip("层");
    m_pTableW->item(0, 2)->setFont(titleFont);
    m_pTableW->item(0, 2)->setTextAlignment(Qt::AlignCenter);

    //column 3 header
    m_pTableW->setItem(0, 3, new QTableWidgetItem("  Repeats  "));
    m_pTableW->item(0, 3)->setBackground(titleBackground);
    m_pTableW->item(0, 3)->setToolTip("重复次数");
    m_pTableW->item(0, 3)->setFont(titleFont);
    m_pTableW->item(0, 3)->setTextAlignment(Qt::AlignCenter);


    int epitaxy = static_cast<int>(m_pdt->at(0).at(0).first.x());
    int DBR = static_cast<int>(m_pdt->at(0).at(1).first.x());
    double lamda = m_pdt->at(0).at(2).first.x();
    double nGaAs = m_pdt->at(0).at(3).first.x();
    double nAl01GaAs = m_pdt->at(0).at(4).first.x();
    double nAlAs = m_pdt->at(0).at(5).first.x();
    double nAl09GaAs = m_pdt->at(0).at(6).first.x();
    int Barrier = static_cast<int>(m_pdt->at(0).at(7).first.x());
    double dwell = m_pdt->at(0).at(8).first.x();
    double nInGaAs = m_pdt->at(0).at(9).first.x();
    double nGaAsP = m_pdt->at(0).at(10).first.x();
    int compensation = static_cast<int>(m_pdt->at(0).at(11).first.x());
    double GaAsPThickness = m_pdt->at(0).at(12).first.x();
    double Nwell = m_pdt->at(0).at(13).first.x();
    double In = m_pdt->at(0).at(14).first.x();
    int resonant = static_cast<int>(m_pdt->at(0).at(15).first.x());
    double nAl06GaAs = m_pdt->at(0).at(16).first.x();

    QString DBRlay1A(QString(""));
    QString DBRlay2A(QString(""));
    QString Barrierlay1A(QString(""));
    QString Compensationlay1A(QString(""));
    QString InGaAsWell(QString(""));
    QString Compensationlay2A(QString(""));
    QString BarrierlayA(QString(""));
    QString Barrierlay2A(QString(""));
    QString WindowlayA(QString(""));
    QString CaplayA(QString(""));

    double DBRlay1B(0);
    double DBRlay2B(0);
    double Barrierlay1B(0);
    double Compensationlay1B(0);
    double Compensationlay2B(0);
    double BarrierlayB(0);
    double Barrierlay2B(0);
    double WindowlayB(0);
    double CaplayB(10);

    if(DBR == 1 || DBR==2){
        DBRlay1A = QString("GaAs");
        DBRlay1B = lamda / 4 / nGaAs;
    }
    else if(DBR == 3){
        DBRlay1A = QString("Al(0.1)GaAs");
        DBRlay1B=lamda / 4 / nAl01GaAs;
    }

    if(DBR == 1){
        DBRlay2A = QString("AlAs");
        DBRlay2B = lamda / 4 / nAlAs;
    }
    else if(DBR == 2 || DBR == 3){
        DBRlay2A = QString("Al(0.9)GaAs");
        DBRlay2B = lamda / 4 / nAl09GaAs;
    }

    if(Barrier == 1){
        Barrierlay1A = QString("GaAs");
        Barrierlay1B = (lamda / 2 - dwell / 2 * nInGaAs) / nGaAs;
    }
    else if(Barrier == 2){
        Barrierlay1A = QString("Al(0.1)GaAs");
        Barrierlay1B = (lamda / 2 - dwell / 2 * nInGaAs) / nAl01GaAs;
    }
    else if(Barrier == 3){
        Barrierlay1A = QString("GaAsP(0.06)");
        Barrierlay1B = (lamda / 2 - dwell / 2 * nInGaAs) / nGaAsP;
    }

    Compensationlay1A = QString("GaAsP(0.06)");
    if(compensation == 0){
        Compensationlay1B = 0;
    }
    else if(compensation == 1){
        Compensationlay1B = GaAsPThickness / 2;
        if(Barrier == 1)
            Barrierlay1B = (lamda/2 - dwell/2*nInGaAs - GaAsPThickness/2*nGaAsP) / nGaAs;  //update Barrierlay1B
        else if(Barrier == 2)
            Barrierlay1B = (lamda/2 - dwell/2*nInGaAs - GaAsPThickness/2*nGaAsP) / nAl01GaAs;
        else if(Barrier == 3)
            Barrierlay1B= (lamda/2 - dwell/2*nInGaAs - GaAsPThickness/2*nGaAsP) / nGaAsP;
    }

    //QString::number(ri_p[i]->Get(1, j), 'g', 2);  //'g' means scitific indicate, significant digits has 2.  'f' means Two decimal places
    InGaAsWell = QString("In(") + QString::number(In, 'g', 3) + QString(")");

    Compensationlay2A=QString("GaAsP(0.06)");
    if(compensation == 0)
        Compensationlay2B = 0;
    else if(compensation == 1)
        Compensationlay2B = GaAsPThickness / 2;

    if(Barrier == 1){
        BarrierlayA = QString("GaAs");
        Barrierlay2A = QString("GaAs");
    }
    else if(Barrier == 2){
        BarrierlayA = QString("Al(0.1)GaAs");
        Barrierlay2A = QString("Al(0.1)GaAs");
    }
    else if(Barrier == 3){
        BarrierlayA = QString("GaAsP(0.06)");
        Barrierlay2A = QString("GaAsP(0.06)");
    }

    if(compensation == 0){
        if(Barrier == 1){
            BarrierlayB = (lamda/2 - dwell*nInGaAs)/ nGaAs;
            Barrierlay2B = (lamda/2 - dwell/2*nInGaAs) / nGaAs;
        }
        else if(Barrier == 2){
            BarrierlayB = (lamda/2 - dwell*nInGaAs) / nAl01GaAs;
            Barrierlay2B = (lamda/2 - dwell/2*nInGaAs) / nAl01GaAs;
        }
        else if(Barrier == 3){
            BarrierlayB = (lamda/2 - dwell*nInGaAs) / nGaAsP;
            Barrierlay2B = (lamda/2 - dwell/2*nInGaAs) / nGaAsP;
        }
    }
    else if(compensation == 1){
        if(Barrier == 1){
            BarrierlayB = (lamda/2 - dwell*nInGaAs - GaAsPThickness/2*nGaAsP) / nGaAs;
            Barrierlay2B = (lamda/2 - dwell/2*nInGaAs - GaAsPThickness/2*nGaAsP) / nGaAs;
        }
        else if(Barrier == 2){
            BarrierlayB = (lamda/2 - dwell*nInGaAs - GaAsPThickness/2*nGaAsP) / nAl01GaAs;
            Barrierlay2B = (lamda/2 - dwell/2*nInGaAs - GaAsPThickness/2*nGaAsP) / nAl01GaAs;
        }
        else if(Barrier == 3){
            BarrierlayB = (lamda/2 - dwell*nInGaAs - GaAsPThickness/2*nGaAsP) / nGaAsP;
            Barrierlay2B = (lamda/2 - dwell/2*nInGaAs - GaAsPThickness/2*nGaAsP) / nGaAsP;
        }
    }

    WindowlayA = QString("Al(0.6)GaAs");
    if(resonant == 1)
        WindowlayB = (lamda - 10*nGaAs)/nAl06GaAs;
    else if(resonant == 2)
        WindowlayB=(5*lamda/4-10*nGaAs)/nAl06GaAs;
    else if(resonant == 3)
        WindowlayB=(4.5*lamda/4-10*nGaAs)/nAl06GaAs;

    CaplayA = QString("GaAs");
    CaplayB = 10;



    if(m_pdt != nullptr && m_pdt->count() != 0){
        if(epitaxy == 1){
            setWindowTitle(QString("芯片外延结构 - 正序"));
            //column 0
            m_pTableW->setItem(1, 0, new QTableWidgetItem(QString("GaAs")));  //2
            m_pTableW->item(1, 0)->setFont(contentFont);
            m_pTableW->item(1, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(2, 0, new QTableWidgetItem(QString("GaAs")));  //3
            m_pTableW->item(2, 0)->setFont(contentFont);
            m_pTableW->item(2, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(3, 0, new QTableWidgetItem(DBRlay1A));         //4
            m_pTableW->item(3, 0)->setFont(contentFont);
            m_pTableW->item(3, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(4, 0, new QTableWidgetItem(DBRlay2A));         //5
            m_pTableW->item(4, 0)->setFont(contentFont);
            m_pTableW->item(4, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(5, 0, new QTableWidgetItem(Barrierlay1A));      //6
            m_pTableW->item(5, 0)->setFont(contentFont);
            m_pTableW->item(5, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(6, 0, new QTableWidgetItem(Compensationlay1A));  //7
            m_pTableW->item(6, 0)->setFont(contentFont);
            m_pTableW->item(6, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(7, 0, new QTableWidgetItem(InGaAsWell));         //8
            m_pTableW->item(7, 0)->setFont(contentFont);
            m_pTableW->item(7, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(8, 0, new QTableWidgetItem(Compensationlay2A));   //9
            m_pTableW->item(8, 0)->setFont(contentFont);
            m_pTableW->item(8, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(9, 0, new QTableWidgetItem(BarrierlayA));        //10
            m_pTableW->item(9, 0)->setFont(contentFont);
            m_pTableW->item(9, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(10, 0, new QTableWidgetItem(Barrierlay2A));      //11
            m_pTableW->item(10, 0)->setFont(contentFont);
            m_pTableW->item(10, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(11, 0, new QTableWidgetItem(WindowlayA));        //12
            m_pTableW->item(11, 0)->setFont(contentFont);
            m_pTableW->item(11, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(12, 0, new QTableWidgetItem(CaplayA));           //13
            m_pTableW->item(12, 0)->setFont(contentFont);
            m_pTableW->item(12, 0)->setTextAlignment(Qt::AlignCenter);

            //column 1
            m_pTableW->setItem(1, 1, new QTableWidgetItem(QString("350um")));  //2
            m_pTableW->item(1, 1)->setFont(contentFont);
            m_pTableW->item(1, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(2, 1, new QTableWidgetItem(QString("100")));  //3
            m_pTableW->item(2, 1)->setFont(contentFont);
            m_pTableW->item(2, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(3, 1, new QTableWidgetItem(QString::number(DBRlay1B)));         //4
            m_pTableW->item(3, 1)->setFont(contentFont);
            m_pTableW->item(3, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(4, 1, new QTableWidgetItem(QString::number(DBRlay2B)));         //5
            m_pTableW->item(4, 1)->setFont(contentFont);
            m_pTableW->item(4, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(5, 1, new QTableWidgetItem(QString::number(Barrierlay1B)));      //6
            m_pTableW->item(5, 1)->setFont(contentFont);
            m_pTableW->item(5, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(6, 1, new QTableWidgetItem(QString::number(Compensationlay1B)));  //7
            m_pTableW->item(6, 1)->setFont(contentFont);
            m_pTableW->item(6, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(7, 1, new QTableWidgetItem(QString::number(dwell)));         //8
            m_pTableW->item(7, 1)->setFont(contentFont);
            m_pTableW->item(7, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(8, 1, new QTableWidgetItem(QString::number(Compensationlay2B)));   //9
            m_pTableW->item(8, 1)->setFont(contentFont);
            m_pTableW->item(8, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(9, 1, new QTableWidgetItem(QString::number(BarrierlayB)));        //10
            m_pTableW->item(9, 1)->setFont(contentFont);
            m_pTableW->item(9, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(10, 1, new QTableWidgetItem(QString::number(Barrierlay2B)));      //11
            m_pTableW->item(10, 1)->setFont(contentFont);
            m_pTableW->item(10, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(11, 1, new QTableWidgetItem(QString::number(WindowlayB)));        //12
            m_pTableW->item(11, 1)->setFont(contentFont);
            m_pTableW->item(11, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(12, 1, new QTableWidgetItem(QString::number(CaplayB)));           //13
            m_pTableW->item(12, 1)->setFont(contentFont);
            m_pTableW->item(12, 1)->setTextAlignment(Qt::AlignCenter);

            //column 2
            m_pTableW->setItem(1, 2, new QTableWidgetItem(QString("Substrate")));  //2
            m_pTableW->item(1, 2)->setFont(contentFont);
            m_pTableW->item(1, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(2, 2, new QTableWidgetItem(QString("Buffer layer")));  //3
            m_pTableW->item(2, 2)->setFont(contentFont);
            m_pTableW->item(2, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(3, 2, new QTableWidgetItem(QString("DBR layer 1")));         //4
            m_pTableW->item(3, 2)->setFont(contentFont);
            m_pTableW->item(3, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(4, 2, new QTableWidgetItem(QString("DBR layer 2")));         //5
            m_pTableW->item(4, 2)->setFont(contentFont);
            m_pTableW->item(4, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(5, 2, new QTableWidgetItem(QString("Barrier layer")));      //6
            m_pTableW->item(5, 2)->setFont(contentFont);
            m_pTableW->item(5, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(6, 2, new QTableWidgetItem(QString("Compensation layer")));  //7
            m_pTableW->item(6, 2)->setFont(contentFont);
            m_pTableW->item(6, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(7, 2, new QTableWidgetItem(QString("Well")));         //8
            m_pTableW->item(7, 2)->setFont(contentFont);
            m_pTableW->item(7, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(8, 2, new QTableWidgetItem(QString("Compensation layer")));   //9
            m_pTableW->item(8, 2)->setFont(contentFont);
            m_pTableW->item(8, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(9, 2, new QTableWidgetItem(QString("Barrier")));        //10
            m_pTableW->item(9, 2)->setFont(contentFont);
            m_pTableW->item(9, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(10, 2, new QTableWidgetItem(QString("Barrier layer")));      //11
            m_pTableW->item(10, 2)->setFont(contentFont);
            m_pTableW->item(10, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(11, 2, new QTableWidgetItem(QString("Window layer")));        //12
            m_pTableW->item(11, 2)->setFont(contentFont);
            m_pTableW->item(11, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(12, 2, new QTableWidgetItem(QString("Protect layer")));           //13
            m_pTableW->item(12, 2)->setFont(contentFont);
            m_pTableW->item(12, 2)->setTextAlignment(Qt::AlignCenter);

            //column 3
            m_pTableW->setItem(1, 3, new QTableWidgetItem(QString("")));  //2
            m_pTableW->item(1, 3)->setFont(contentFont);
            m_pTableW->item(1, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(2, 3, new QTableWidgetItem(QString("")));  //3
            m_pTableW->item(2, 3)->setFont(contentFont);
            m_pTableW->item(2, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(3, 3, new QTableWidgetItem(QString("25")));         //4
            m_pTableW->item(3, 3)->setFont(contentFont);
            m_pTableW->item(3, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(4, 3, new QTableWidgetItem(QString("25")));         //5
            m_pTableW->item(4, 3)->setFont(contentFont);
            m_pTableW->item(4, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(5, 3, new QTableWidgetItem(QString("")));      //6
            m_pTableW->item(5, 3)->setFont(contentFont);
            m_pTableW->item(5, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(6, 3, new QTableWidgetItem(QString::number(Nwell)));  //7
            m_pTableW->item(6, 3)->setFont(contentFont);
            m_pTableW->item(6, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(7, 3, new QTableWidgetItem(QString::number(Nwell)));         //8
            m_pTableW->item(7, 3)->setFont(contentFont);
            m_pTableW->item(7, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(8, 3, new QTableWidgetItem(QString::number(Nwell)));   //9
            m_pTableW->item(8, 3)->setFont(contentFont);
            m_pTableW->item(8, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(9, 3, new QTableWidgetItem(QString::number(Nwell-1)));        //10
            m_pTableW->item(9, 3)->setFont(contentFont);
            m_pTableW->item(9, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(10, 3, new QTableWidgetItem(QString("")));      //11
            m_pTableW->item(10, 3)->setFont(contentFont);
            m_pTableW->item(10, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(11, 3, new QTableWidgetItem(QString("")));        //12
            m_pTableW->item(11, 3)->setFont(contentFont);
            m_pTableW->item(11, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(12, 3, new QTableWidgetItem(QString("")));           //13
            m_pTableW->item(12, 3)->setFont(contentFont);
            m_pTableW->item(12, 3)->setTextAlignment(Qt::AlignCenter);

        }
        else if(epitaxy == 2){
            setWindowTitle(QString("芯片外延结构 - 逆序 Reverse"));
            //column 0
            m_pTableW->setItem(1, 0, new QTableWidgetItem(QString("GaAs")));  //2
            m_pTableW->item(1, 0)->setFont(contentFont);
            m_pTableW->item(1, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(2, 0, new QTableWidgetItem(QString("GaAs")));  //3
            m_pTableW->item(2, 0)->setFont(contentFont);
            m_pTableW->item(2, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(3, 0, new QTableWidgetItem(QString("GaAsP(0.6)")));  //4
            m_pTableW->item(3, 0)->setFont(contentFont);
            m_pTableW->item(3, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(4, 0, new QTableWidgetItem(CaplayA));         //5
            m_pTableW->item(4, 0)->setFont(contentFont);
            m_pTableW->item(4, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(5, 0, new QTableWidgetItem(WindowlayA));      //6
            m_pTableW->item(5, 0)->setFont(contentFont);
            m_pTableW->item(5, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(6, 0, new QTableWidgetItem(Barrierlay2A));     //7
            m_pTableW->item(6, 0)->setFont(contentFont);
            m_pTableW->item(6, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(7, 0, new QTableWidgetItem(BarrierlayA));         //8
            m_pTableW->item(7, 0)->setFont(contentFont);
            m_pTableW->item(7, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(8, 0, new QTableWidgetItem(Compensationlay2A));   //9
            m_pTableW->item(8, 0)->setFont(contentFont);
            m_pTableW->item(8, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(9, 0, new QTableWidgetItem(InGaAsWell));        //10
            m_pTableW->item(9, 0)->setFont(contentFont);
            m_pTableW->item(9, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(10, 0, new QTableWidgetItem(Compensationlay1A));   //11
            m_pTableW->item(10, 0)->setFont(contentFont);
            m_pTableW->item(10, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(11, 0, new QTableWidgetItem(Barrierlay1A));        //12
            m_pTableW->item(11, 0)->setFont(contentFont);
            m_pTableW->item(11, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(12, 0, new QTableWidgetItem(DBRlay2A));           //13
            m_pTableW->item(12, 0)->setFont(contentFont);
            m_pTableW->item(12, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(13, 0, new QTableWidgetItem(DBRlay1A));           //14
            m_pTableW->item(13, 0)->setFont(contentFont);
            m_pTableW->item(13, 0)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(14, 0, new QTableWidgetItem(QString("GaAs")));    //15
            m_pTableW->item(14, 0)->setFont(contentFont);
            m_pTableW->item(14, 0)->setTextAlignment(Qt::AlignCenter);

            //column 1
            m_pTableW->setItem(1, 1, new QTableWidgetItem(QString("350um")));  //2
            m_pTableW->item(1, 1)->setFont(contentFont);
            m_pTableW->item(1, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(2, 1, new QTableWidgetItem(QString("100")));  //3
            m_pTableW->item(2, 1)->setFont(contentFont);
            m_pTableW->item(2, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(3, 1, new QTableWidgetItem(QString("100")));         //4
            m_pTableW->item(3, 1)->setFont(contentFont);
            m_pTableW->item(3, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(4, 1, new QTableWidgetItem(QString::number(CaplayB)));         //5
            m_pTableW->item(4, 1)->setFont(contentFont);
            m_pTableW->item(4, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(5, 1, new QTableWidgetItem(QString::number(WindowlayB)));      //6
            m_pTableW->item(5, 1)->setFont(contentFont);
            m_pTableW->item(5, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(6, 1, new QTableWidgetItem(QString::number(Barrierlay2B)));  //7
            m_pTableW->item(6, 1)->setFont(contentFont);
            m_pTableW->item(6, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(7, 1, new QTableWidgetItem(QString::number(BarrierlayB)));         //8
            m_pTableW->item(7, 1)->setFont(contentFont);
            m_pTableW->item(7, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(8, 1, new QTableWidgetItem(QString::number(Compensationlay2B)));   //9
            m_pTableW->item(8, 1)->setFont(contentFont);
            m_pTableW->item(8, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(9, 1, new QTableWidgetItem(QString::number(dwell)));        //10
            m_pTableW->item(9, 1)->setFont(contentFont);
            m_pTableW->item(9, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(10, 1, new QTableWidgetItem(QString::number(Compensationlay1B)));      //11
            m_pTableW->item(10, 1)->setFont(contentFont);
            m_pTableW->item(10, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(11, 1, new QTableWidgetItem(QString::number(Barrierlay1B)));        //12
            m_pTableW->item(11, 1)->setFont(contentFont);
            m_pTableW->item(11, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(12, 1, new QTableWidgetItem(QString::number(DBRlay2B)));           //13
            m_pTableW->item(12, 1)->setFont(contentFont);
            m_pTableW->item(12, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(13, 1, new QTableWidgetItem(QString::number(DBRlay1B)));           //14
            m_pTableW->item(13, 1)->setFont(contentFont);
            m_pTableW->item(13, 1)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(14, 1, new QTableWidgetItem(QString("10")));    //15
            m_pTableW->item(14, 1)->setFont(contentFont);
            m_pTableW->item(14, 1)->setTextAlignment(Qt::AlignCenter);

            //column 2
            m_pTableW->setItem(1, 2, new QTableWidgetItem(QString("Substrate")));  //2
            m_pTableW->item(1, 2)->setFont(contentFont);
            m_pTableW->item(1, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(2, 2, new QTableWidgetItem(QString("Buffer layer")));  //3
            m_pTableW->item(2, 2)->setFont(contentFont);
            m_pTableW->item(2, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(3, 2, new QTableWidgetItem(QString("Etch stop layer")));         //4
            m_pTableW->item(3, 2)->setFont(contentFont);
            m_pTableW->item(3, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(4, 2, new QTableWidgetItem(QString("Protect layer")));         //5
            m_pTableW->item(4, 2)->setFont(contentFont);
            m_pTableW->item(4, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(5, 2, new QTableWidgetItem(QString("Window layer")));      //6
            m_pTableW->item(5, 2)->setFont(contentFont);
            m_pTableW->item(5, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(6, 2, new QTableWidgetItem(QString("Barrier layer")));  //7
            m_pTableW->item(6, 2)->setFont(contentFont);
            m_pTableW->item(6, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(7, 2, new QTableWidgetItem(QString("Barrier")));         //8
            m_pTableW->item(7, 2)->setFont(contentFont);
            m_pTableW->item(7, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(8, 2, new QTableWidgetItem(QString("Compensation layer")));   //9
            m_pTableW->item(8, 2)->setFont(contentFont);
            m_pTableW->item(8, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(9, 2, new QTableWidgetItem(QString("Well")));        //10
            m_pTableW->item(9, 2)->setFont(contentFont);
            m_pTableW->item(9, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(10, 2, new QTableWidgetItem(QString("Compensation layer")));      //11
            m_pTableW->item(10, 2)->setFont(contentFont);
            m_pTableW->item(10, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(11, 2, new QTableWidgetItem(QString("Barrier layer")));        //12
            m_pTableW->item(11, 2)->setFont(contentFont);
            m_pTableW->item(11, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(12, 2, new QTableWidgetItem(QString("DBR layer 2")));           //13
            m_pTableW->item(12, 2)->setFont(contentFont);
            m_pTableW->item(12, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(13, 2, new QTableWidgetItem(QString("DBR layer 1")));           //14
            m_pTableW->item(13, 2)->setFont(contentFont);
            m_pTableW->item(13, 2)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(14, 2, new QTableWidgetItem(QString("Top layer")));    //15
            m_pTableW->item(14, 2)->setFont(contentFont);
            m_pTableW->item(14, 2)->setTextAlignment(Qt::AlignCenter);

            //column 3
            m_pTableW->setItem(1, 3, new QTableWidgetItem(QString("")));  //2
            m_pTableW->item(1, 3)->setFont(contentFont);
            m_pTableW->item(1, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(2, 3, new QTableWidgetItem(QString("")));  //3
            m_pTableW->item(2, 3)->setFont(contentFont);
            m_pTableW->item(2, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(3, 3, new QTableWidgetItem(QString("")));         //4
            m_pTableW->item(3, 3)->setFont(contentFont);
            m_pTableW->item(3, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(4, 3, new QTableWidgetItem(QString("")));         //5
            m_pTableW->item(4, 3)->setFont(contentFont);
            m_pTableW->item(4, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(5, 3, new QTableWidgetItem(QString("")));      //6
            m_pTableW->item(5, 3)->setFont(contentFont);
            m_pTableW->item(5, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(6, 3, new QTableWidgetItem(QString("")));    //7
            m_pTableW->item(6, 3)->setFont(contentFont);
            m_pTableW->item(6, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(7, 3, new QTableWidgetItem(QString::number(Nwell-1)));         //8
            m_pTableW->item(7, 3)->setFont(contentFont);
            m_pTableW->item(7, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(8, 3, new QTableWidgetItem(QString::number(Nwell)));   //9
            m_pTableW->item(8, 3)->setFont(contentFont);
            m_pTableW->item(8, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(9, 3, new QTableWidgetItem(QString::number(Nwell)));        //10
            m_pTableW->item(9, 3)->setFont(contentFont);
            m_pTableW->item(9, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(10, 3, new QTableWidgetItem(QString::number(Nwell)));      //11
            m_pTableW->item(10, 3)->setFont(contentFont);
            m_pTableW->item(10, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(11, 3, new QTableWidgetItem(QString("")));        //12
            m_pTableW->item(11, 3)->setFont(contentFont);
            m_pTableW->item(11, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(12, 3, new QTableWidgetItem(QString("25")));           //13
            m_pTableW->item(12, 3)->setFont(contentFont);
            m_pTableW->item(12, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(13, 3, new QTableWidgetItem(QString("25")));           //14
            m_pTableW->item(13, 3)->setFont(contentFont);
            m_pTableW->item(13, 3)->setTextAlignment(Qt::AlignCenter);

            m_pTableW->setItem(14, 3, new QTableWidgetItem(QString("")));    //15
            m_pTableW->item(14, 3)->setFont(contentFont);
            m_pTableW->item(14, 3)->setTextAlignment(Qt::AlignCenter);


        }
    }

}










