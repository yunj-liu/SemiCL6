#include "epstructwidget.h"

EpStructWidget::EpStructWidget(QWidget *parent)
    : QWidget{parent}
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(QString("芯片外延结构"));
    setWindowIcon(QIcon(":/imgs/chip-60.png"));
    setWindowFlags(Qt::Dialog);

}
