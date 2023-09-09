#ifndef COMMONCONTROL_H
#define COMMONCONTROL_H
#include <QPointF>

typedef QPair<QPointF, QString> Data;  //need include QWidget
typedef QList<Data> DataList;
typedef QList<DataList> DataTable;
typedef QHash<QString, DataTable> FigureData;


class CommonControl
{
public:
    CommonControl();
    static DataTable getDataTableFromCsvFile(QString filePathName);
    static FigureData getFigureDataHashMapFromCsvFile(QString sFoldName, int figureNum);
    static FigureData generateFigureData();
};

#endif // COMMONCONTROL_H
