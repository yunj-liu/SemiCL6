#ifndef F5_LINEWIDGET_H
#define F5_LINEWIDGET_H

#include "contentwidget.h"
#include "commontype.h"

class F5_LineWidget : public ContentWidget
{
    Q_OBJECT
public:
    F5_LineWidget(QWidget *parent = nullptr, DataTable* figure_datatable = nullptr);
};

#endif // F5_LINEWIDGET_H
