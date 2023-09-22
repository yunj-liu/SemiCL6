#include "refracidxwidget.h"

RefracIdxWidget::RefracIdxWidget(QWidget *parent)
    : QWidget{parent}
{
    setWindowModality(Qt::ApplicationModal);
    setWindowTitle(QString("外延材料折射率"));
    setWindowIcon(QIcon(":/imgs/refraction-48.png"));
    setWindowFlags(Qt::Dialog);
}
