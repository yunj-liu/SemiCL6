﻿#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QWidget>

namespace Ui {
class AboutWidget;
}

class AboutWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AboutWidget(QWidget *parent = nullptr);
    ~AboutWidget();

private slots:
    void on_pushButton_clicked();

private:
    Ui::AboutWidget *ui;
};

#endif // ABOUTWIDGET_H
