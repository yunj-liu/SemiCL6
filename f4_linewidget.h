#ifndef F4_LINEWIDGET_H
#define F4_LINEWIDGET_H

#include "contentwidget.h"
#include "commoncontrol.h"

class F4_LineWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit F4_LineWidget(QWidget *parent = nullptr, DataTable* figure_datatable = nullptr);
};

#endif // F4_LINEWIDGET_H
