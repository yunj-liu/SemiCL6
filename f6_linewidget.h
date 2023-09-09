#ifndef F6_LINEWIDGET_H
#define F6_LINEWIDGET_H

#include "contentwidget.h"
#include "commoncontrol.h"

class F6_LineWidget : public ContentWidget
{
    Q_OBJECT
public:
    F6_LineWidget(QWidget *parent = nullptr, DataTable* figure_datatable = nullptr);
};

#endif // F6_LINEWIDGET_H
