/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:39.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
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
    static FigureData generateFigureData(double(*pArrInParams)[12]);
    static void saveDataTableToCsvFile(QString sPathName, QString sFileName, DataTable& dt);
    static void saveFigureDataHashMapToCsvFile(QString sFoldName, int figureNum, FigureData &fd);

    static QString getStringFromIndex(int idx);
    static void saveReIdxDTtoCsvFile(QString sPathName, QString sFileName, DataTable& dt);
    static DataTable getReIdxDTfromCsvFile(QString filePathName);
    static QString getStringFromEpStruc(int idx);
    static void saveEpStrucDTtoCsvFile(QString sPathName, QString sFileName, DataTable& dt);
    static DataTable getEpStrucDTfromCsvFile(QString filePathName);
};

#endif // COMMONCONTROL_H
