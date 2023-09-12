/*******************************************************************
* This file was created in Chongqing in 2023-09-10 20:50:10.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#ifndef LTOOLBAR_H
#define LTOOLBAR_H

#include <QToolBar>

class LToolBar : public QToolBar
{
    Q_OBJECT
public:
    explicit LToolBar(const QString &title, QMainWindow *mainWindow);

private:
    QAction *mSetCalcParamAction;

};

#endif // LTOOLBAR_H
