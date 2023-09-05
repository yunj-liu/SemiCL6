#ifndef F7_LINEWIDGET_H
#define F7_LINEWIDGET_H

#include "contentwidget.h"
#include "commontype.h"

class F7_LineWidget : public ContentWidget
{
    Q_OBJECT
public:
    F7_LineWidget(QWidget *parent = nullptr, DataTable* figure_datatable = nullptr);
};

#endif // F7_LINEWIDGET_H
