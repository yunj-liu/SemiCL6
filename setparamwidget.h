/*******************************************************************
* This file was created in Chongqing in 2023-09-11 09:05:40.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/

#ifndef SETPARAMWIDGET_H
#define SETPARAMWIDGET_H

#include <QWidget>
#include <QGroupBox>
#include <QLineEdit>
#include <QRadioButton>
#include "mainwidget.h"

class SetParamWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SetParamWidget(QWidget *parent = nullptr, MainWidget *pMainWidget = nullptr);

private:
    QLineEdit *lineedit1;
    QLineEdit *lineedit2;
    QLineEdit *lineedit3;
    QLineEdit *lineedit4;
    QLineEdit *lineedit5;
    QLineEdit *lineedit6;

    QRadioButton *radiog41;
    QRadioButton *radiog42;
    QRadioButton *radiog43;
    QRadioButton *radiog51;
    QRadioButton *radiog52;
    QRadioButton *radiog61;
    QRadioButton *radiog62;
    QRadioButton *radiog63;
    QRadioButton *radiog71;
    QRadioButton *radiog72;
    QRadioButton *radiog73;
    QRadioButton *radiog81;
    QRadioButton *radiog82;
    QRadioButton *radiog83;
    QRadioButton *radiog91;
    QRadioButton *radiog92;

    QButtonGroup *btnGroup4;
    QButtonGroup *btnGroup5;
    QButtonGroup *btnGroup6;
    QButtonGroup *btnGroup7;
    QButtonGroup *btnGroup8;
    QButtonGroup *btnGroup9;

    MainWidget *m_pMainWidget = nullptr;

private slots:
    void setParamOk();
    void setParamCancel();

signals:

};

#endif // SETPARAMWIDGET_H
