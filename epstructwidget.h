#ifndef EPSTRUCTWIDGET_H
#define EPSTRUCTWIDGET_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "commontype.h"

class EpStructWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit EpStructWidget(DataTable *p_dt = nullptr, QWidget *parent = nullptr);

private:
    QTableWidget *m_pTableW = nullptr;
    void setupContents();
    DataTable *m_pdt = nullptr;
};

#endif // EPSTRUCTWIDGET_H
