/*******************************************************************
* This file was created in Chongqing in 2023-09-10 20:50:22.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#include "ltoolbar.h"

LToolBar::LToolBar(const QString &title, QMainWindow *mainWindow)
{
    setWindowTitle(title);
    setObjectName(title);
    //setIconSize(QSize(32, 32));
    setIconSize(QSize(24, 24));

    mSetCalcParamAction = addAction(QIcon(":/imgs/formula-fx-100.png"), "设置运算参数");
}
