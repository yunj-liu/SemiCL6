#include "refracidxwidget.h"
#include <QLayout>
#include <QHeaderView>

RefracIdxWidget::RefracIdxWidget(DataTable *p_dt, QWidget *parent)
    : QMainWindow{parent}
    , m_pdt(p_dt)
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(QString("外延材料折射率"));
    setWindowIcon(QIcon(":/imgs/refraction-48.png"));
    setWindowFlags(Qt::Dialog);
    //this->layout()->setSizeConstraint(QLayout::SetFixedSize);
    layout()->setSizeConstraint(QLayout::SetFixedSize);  //both ok.

    int rows = 17;
    int cols = 2;
    m_pTableW = new QTableWidget(rows, cols, this);
    m_pTableW->setSizeAdjustPolicy(QTableWidget::AdjustToContents);
    for (int c = 0; c < cols; ++c) {
        QString character(QChar('A' + c));
        m_pTableW->setHorizontalHeaderItem(c, new QTableWidgetItem(character));  //QTableWidget & QTableWidgetItem
    }
    m_pTableW->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //stretch, resizeToContents
    m_pTableW->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);  //all columns set
    m_pTableW->horizontalHeader()->setSectionResizeMode(1, QHeaderView::ResizeToContents);

    m_pTableW->verticalHeader()->setSectionResizeMode(QHeaderView::Stretch);  //all rows set
    for (int r = 0; r < rows; ++r) {
        m_pTableW->verticalHeader()->setSectionResizeMode(r, QHeaderView::ResizeToContents);
    }


    setCentralWidget(m_pTableW);
    setupContents();
    m_pTableW->update();

    statusBar();
}

void RefracIdxWidget::setupContents()
{
    QBrush titleBackground(Qt::lightGray);
    QFont titleFont = m_pTableW->font();
    titleFont.setBold(true);
    titleFont.setPixelSize(40);
    titleFont.setFamily("Times New Roman");

    QFont contentFont = m_pTableW->font();
    contentFont.setPixelSize(25);
    contentFont.setFamily("Cambria");

    //column 0
    m_pTableW->setItem(0, 0, new QTableWidgetItem("  Material  "));
    m_pTableW->item(0, 0)->setBackground(titleBackground);
    m_pTableW->item(0, 0)->setToolTip("外延材料");
    m_pTableW->item(0, 0)->setFont(titleFont);
    m_pTableW->item(0, 0)->setTextAlignment(Qt::AlignCenter);

    if(m_pdt != nullptr && m_pdt->count() != 0)
    {
        m_pTableW->setItem(1, 0, new QTableWidgetItem(m_pdt->at(0).at(0).second));
        m_pTableW->item(1, 0)->setFont(contentFont);
        m_pTableW->item(1, 0)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(2, 0, new QTableWidgetItem(m_pdt->at(0).at(1).second));
        m_pTableW->item(2, 0)->setFont(contentFont);
        m_pTableW->item(2, 0)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(3, 0, new QTableWidgetItem(m_pdt->at(0).at(2).second));
        m_pTableW->item(3, 0)->setFont(contentFont);
        m_pTableW->item(3, 0)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(4, 0, new QTableWidgetItem(m_pdt->at(0).at(3).second));
        m_pTableW->item(4, 0)->setFont(contentFont);
        m_pTableW->item(4, 0)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(5, 0, new QTableWidgetItem(m_pdt->at(0).at(5).second));
        m_pTableW->item(5, 0)->setFont(contentFont);
        m_pTableW->item(5, 0)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(6, 0, new QTableWidgetItem(m_pdt->at(0).at(6).second));
        m_pTableW->item(6, 0)->setFont(contentFont);
        m_pTableW->item(6, 0)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(7, 0, new QTableWidgetItem(m_pdt->at(0).at(7).second));
        m_pTableW->item(7, 0)->setFont(contentFont);
        m_pTableW->item(7, 0)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(8, 0, new QTableWidgetItem(m_pdt->at(0).at(8).second));
        m_pTableW->item(8, 0)->setFont(contentFont);
        m_pTableW->item(8, 0)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(9, 0, new QTableWidgetItem(m_pdt->at(0).at(9).second));
        m_pTableW->item(9, 0)->setFont(contentFont);
        m_pTableW->item(9, 0)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(10, 0, new QTableWidgetItem(QString("")));  //insert blank
        m_pTableW->item(10, 0)->setBackground(titleBackground);

        m_pTableW->setItem(11, 0, new QTableWidgetItem(m_pdt->at(0).at(10).second));
        m_pTableW->item(11, 0)->setFont(contentFont);
        m_pTableW->item(11, 0)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(12, 0, new QTableWidgetItem(m_pdt->at(0).at(11).second));
        m_pTableW->item(12, 0)->setFont(contentFont);
        m_pTableW->item(12, 0)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(13, 0, new QTableWidgetItem(m_pdt->at(0).at(12).second));
        m_pTableW->item(13, 0)->setFont(contentFont);
        m_pTableW->item(13, 0)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(14, 0, new QTableWidgetItem(m_pdt->at(0).at(13).second));
        m_pTableW->item(14, 0)->setFont(contentFont);
        m_pTableW->item(14, 0)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(15, 0, new QTableWidgetItem(m_pdt->at(0).at(14).second));
        m_pTableW->item(15, 0)->setFont(contentFont);
        m_pTableW->item(15, 0)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(16, 0, new QTableWidgetItem(QString("")));  //insert blank
        m_pTableW->item(16, 0)->setBackground(titleBackground);
    }

    //column 1
    m_pTableW->setItem(0, 1, new QTableWidgetItem("  Refractive Index  "));
    m_pTableW->item(0, 1)->setBackground(titleBackground);
    m_pTableW->item(0, 1)->setToolTip("折射率");
    m_pTableW->item(0, 1)->setFont(titleFont);

    if(m_pdt != nullptr && m_pdt->count() != 0){
        m_pTableW->setItem(1, 1, new QTableWidgetItem(QString::number(m_pdt->at(0).at(0).first.x())));
        m_pTableW->item(1, 1)->setFont(contentFont);
        m_pTableW->item(1, 1)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(2, 1, new QTableWidgetItem(QString::number(m_pdt->at(0).at(1).first.x())));
        m_pTableW->item(2, 1)->setFont(contentFont);
        m_pTableW->item(2, 1)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(3, 1, new QTableWidgetItem(QString::number(m_pdt->at(0).at(2).first.x())));
        m_pTableW->item(3, 1)->setFont(contentFont);
        m_pTableW->item(3, 1)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(4, 1, new QTableWidgetItem(QString::number(m_pdt->at(0).at(3).first.x())));
        m_pTableW->item(4, 1)->setFont(contentFont);
        m_pTableW->item(4, 1)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(5, 1, new QTableWidgetItem(QString::number(m_pdt->at(0).at(5).first.x())));
        m_pTableW->item(5, 1)->setFont(contentFont);
        m_pTableW->item(5, 1)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(6, 1, new QTableWidgetItem(QString::number(m_pdt->at(0).at(6).first.x())));
        m_pTableW->item(6, 1)->setFont(contentFont);
        m_pTableW->item(6, 1)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(7, 1, new QTableWidgetItem(QString::number(m_pdt->at(0).at(7).first.x())));
        m_pTableW->item(7, 1)->setFont(contentFont);
        m_pTableW->item(7, 1)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(8, 1, new QTableWidgetItem(QString::number(m_pdt->at(0).at(8).first.x())));
        m_pTableW->item(8, 1)->setFont(contentFont);
        m_pTableW->item(8, 1)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(9, 1, new QTableWidgetItem(QString::number(m_pdt->at(0).at(9).first.x())));  //GaAsP(0.06)
        m_pTableW->item(9, 1)->setFont(contentFont);
        m_pTableW->item(9, 1)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(10, 1, new QTableWidgetItem(QString("")));  //insert blank
        m_pTableW->item(10, 1)->setBackground(titleBackground);
        m_pTableW->item(10, 1)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(11, 1, new QTableWidgetItem(QString::number(m_pdt->at(0).at(10).first.x())));
        m_pTableW->item(11, 1)->setFont(contentFont);
        m_pTableW->item(11, 1)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(12, 1, new QTableWidgetItem(QString::number(m_pdt->at(0).at(11).first.x())));
        m_pTableW->item(12, 1)->setFont(contentFont);
        m_pTableW->item(12, 1)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(13, 1, new QTableWidgetItem(QString::number(m_pdt->at(0).at(12).first.x())));
        m_pTableW->item(13, 1)->setFont(contentFont);
        m_pTableW->item(13, 1)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(14, 1, new QTableWidgetItem(QString("None")));  //InGaAs Critical Thickness
        m_pTableW->item(14, 1)->setFont(contentFont);
        m_pTableW->item(14, 1)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(15, 1, new QTableWidgetItem(QString::number(m_pdt->at(0).at(14).first.x())));
        m_pTableW->item(15, 1)->setFont(contentFont);
        m_pTableW->item(15, 1)->setTextAlignment(Qt::AlignCenter);

        m_pTableW->setItem(16, 1, new QTableWidgetItem(QString("")));  //insert blank
        m_pTableW->item(16, 1)->setBackground(titleBackground);
    }

}
