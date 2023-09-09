#ifndef F1_LINEWIDGET_H
#define F1_LINEWIDGET_H

#include "contentwidget.h"
#include "commoncontrol.h"

class F1_LineWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit F1_LineWidget(QWidget *parent = nullptr, DataTable* figure_datatable = nullptr);
};

#endif // F1_LINEWIDGET_H
