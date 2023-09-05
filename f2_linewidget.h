#ifndef F2_LINEWIDGET_H
#define F2_LINEWIDGET_H

#include "contentwidget.h"
#include "commontype.h"

class F2_LineWidget : public ContentWidget
{
    Q_OBJECT
public:
    explicit F2_LineWidget(QWidget *parent = nullptr, DataTable* figure_datatable = nullptr);
};

#endif // F2_LINEWIDGET_H
