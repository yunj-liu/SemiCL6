#ifndef REFRACIDXWIDGET_H
#define REFRACIDXWIDGET_H

#include <QMainWindow>
#include <QTableWidget>
#include <QTableWidgetItem>
#include "commontype.h"

//QT_BEGIN_NAMESPACE
//class QTableWidgetItem;
//class QTableWidget;
//QT_END_NAMESPACE

class RefracIdxWidget : public QMainWindow
{
    Q_OBJECT
public:
    explicit RefracIdxWidget(DataTable *p_dt = nullptr, QWidget *parent = nullptr);

private:
    QTableWidget *m_pTableW = nullptr;
    void setupContents();
    DataTable *m_pdt = nullptr;
};

#endif // REFRACIDXWIDGET_H
