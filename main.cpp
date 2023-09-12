/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:39.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
//#include "mainwidget.h"
#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication myapp(argc, argv);
    //MainWidget w;
    //w.show();
    MainWindow mainWin;
    mainWin.setMinimumSize(1000, 500);
    mainWin.resize(1800, 900);
    mainWin.show();

    return myapp.exec();
}
