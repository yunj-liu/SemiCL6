#ifndef F3_LINEWIDGET_H
#define F3_LINEWIDGET_H

#include "contentwidget.h"
#include "commoncontrol.h"

class F3_LineWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit F3_LineWidget(QWidget *parent = nullptr, DataTable* figure_datatable = nullptr);
};

#endif // F3_LINEWIDGET_H
