/*******************************************************************
* This file was created in Chongqing in 2023-09-09 22:30:39.       *
* Written by Yun-Jie Liu.                                          *
* <email: liu.yunjie@qq.com>                                       *
********************************************************************/
#include "commoncontrol.h"
#include <QFile>
#include <QDir>
#include "SemiCL6Func.h"
#include <QMessageBox>


CommonControl::CommonControl()
{

}

DataTable CommonControl::getDataTableFromCsvFile(QString filePathName)
{
    DataTable dt;
    QFile file;
    file.setFileName(filePathName);
    if(!file.exists()){
        return dt;
    }
    QString line;
    QStringList lineitem;
    int row=0;
    if(file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QTextStream in_stream(&file);
        int listCount=0;
        if(!in_stream.atEnd()){ //Handle the first line first,for get listCount define datalistArray
            line = in_stream.readLine();
            if(!line.isEmpty()){
                lineitem = line.split(',');
                listCount = lineitem.count() - 1;  //the first col is the coordinate x, so the num of lists must sub 1
                DataList *datalistArray = new DataList[listCount];
                for(int j(0); j<listCount; j++){
                    QPointF value(lineitem.at(0).toDouble(), lineitem.at(j+1).toDouble());  //lineitem.at(0) is coordinate x
                    QString label = "Slice " + QString::number(row) + ":" + QString::number(j);
                    datalistArray[j] << Data(value, label);
                }
                row = row + 1;

                //Continue with the remaining lines
                while(!in_stream.atEnd()){
                    line = in_stream.readLine();
                    if(!line.isEmpty()){
                        lineitem = line.split(',');
                        for(int j(0); j<listCount; j++){
                            if(!(lineitem.at(j+1).isEmpty() || lineitem.at(j+1).isNull())){  //figure6 last col only has one number, so the remaining row in last col not append data in list
                                QPointF value(lineitem.at(0).toDouble(), lineitem.at(j+1).toDouble());
                                QString label = "Slice " + QString::number(row) + ":" + QString::number(j);
                                datalistArray[j] << Data(value, label);
                            }
                        }
                        row++;
                    }
                }
                for(int j(0); j<listCount; j++){
                    dt << datalistArray[j];
                }
            }
        }
        file.close();
    }
    return dt;
}

FigureData CommonControl::getFigureDataHashMapFromCsvFile(QString sFoldName, int figureNum)
{
    FigureData datatableMap;
    if(!sFoldName.startsWith('/')){
        sFoldName = "/" + sFoldName;
    }
    if(!sFoldName.endsWith('/')){
        sFoldName += "/";
    }
    QString sPathName;
    QString currend_path(QDir::currentPath());
    sPathName = currend_path + sFoldName;
    //not confirm the path exist or not, if the dir is not exist, so the getDataTableFromCsvFile return empty dt, the dt's count is 0
    //but key must in hash map, eg "figure1", etc, dt can be the empty, means it's count is zero
    //QDir dir(sPathName);
    //if(dir.exists())
    for(int i(1); i<=figureNum; i++){
        DataTable dt = CommonControl::getDataTableFromCsvFile(sPathName+"figure"+QString::number(i)+".csv");
        datatableMap.insert("figure"+QString::number(i), dt);
    }
    return datatableMap;
}

FigureData CommonControl::generateFigureData(double(*pArrInParams)[12]){
    FigureData datatableMap;
    if (!SemiCL6FuncInitialize()) // DLL Initialize
    {
        QMessageBox msgBox;
        msgBox.setText("SemiCL DLL initialization failed.");
        msgBox.exec();
    }
    //figure1 array. num of rows and cols must pre define
    mwArray matrix_f1_x(1, 1120, mxDOUBLE_CLASS, mxREAL);    //first 2 param indicate rowCnt, colCnt. 1 row,1120 cols, store in col priority , also means 1 col, 1120 rows.
    mwArray matrix_f1_ph1(1, 1120, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f1_ph2(1, 1120, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f1_ph3(1, 1120, mxDOUBLE_CLASS, mxREAL);
    //figure2 array
    mwArray matrix_f2_x(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f2_E1(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f2_E2(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f2_E3(1, 81, mxDOUBLE_CLASS, mxREAL);
    //figure3 array
    mwArray matrix_f3_x(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f3_HH1(1, 81, mxDOUBLE_CLASS, mxREAL);  //in matlab the array is 81*1, but use 1*81 there can still read the data
    mwArray matrix_f3_HH2(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f3_HH3(1, 81, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f3_LH1(1, 81, mxDOUBLE_CLASS, mxREAL);
    //figure4 array
    mwArray matrix_f4_x(1, 301, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f4_gai(1, 301, mxDOUBLE_CLASS, mxREAL);
    //figure5 array
    mwArray matrix_f5_x(1, 301, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f5_ref(1, 301, mxDOUBLE_CLASS, mxREAL);

    //figure6 array
    //mwArray matrix_f6_x(1, 9252, mxDOUBLE_CLASS, mxREAL);
    //mwArray matrix_f6_YYy(1, 9252, mxDOUBLE_CLASS, mxREAL);
    //mwArray matrix_f6_mm1(1, 1, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f6_x(mxDOUBLE_CLASS);  //The number of rows and columns is uncertain
    mwArray matrix_f6_YYy(mxDOUBLE_CLASS);
    mwArray matrix_f6_mm1(1, 1, mxDOUBLE_CLASS, mxREAL);


    //figure7 array
    mwArray matrix_f7_x(1, 301, mxDOUBLE_CLASS, mxREAL);
    mwArray matrix_f7_TT(1, 301, mxDOUBLE_CLASS, mxREAL);

    //In params, pass into matlab dll
    mwArray matrix_inParams(1, 12, mxDOUBLE_CLASS, mxREAL);  // 12 is the num of InParams, pass 12 params into matlab dll
    matrix_inParams.SetData(*pArrInParams, 12);


    int nargout=22;      // the number of return params. must correct. i.e. num of out params
    SemiCL6Func(nargout,
                matrix_f1_x, matrix_f1_ph1, matrix_f1_ph2, matrix_f1_ph3,
                matrix_f2_x, matrix_f2_E1, matrix_f2_E2, matrix_f2_E3,
                matrix_f3_x, matrix_f3_HH1, matrix_f3_HH2, matrix_f3_HH3, matrix_f3_LH1,
                matrix_f4_x, matrix_f4_gai,
                matrix_f5_x, matrix_f5_ref,
                matrix_f6_x, matrix_f6_YYy, matrix_f6_mm1,
                matrix_f7_x, matrix_f7_TT,
                //below, the 23 param is the In params
                matrix_inParams
                );
    //test
    //qDebug() << *s1;
    //qDebug() << s1[1];

    //end of test
    int listCount(0);
    int valueCount(0);

    //figure 1
    listCount = 3;
    valueCount = 1120;
    mwArray* f1_ph[3];
    f1_ph[0] = &matrix_f1_ph1;
    f1_ph[1] = &matrix_f1_ph2;
    f1_ph[2] = &matrix_f1_ph3;
    DataTable datatable_figure1;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f1_x.Get(1, j+1), f1_ph[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure1 << dataList;
    }
    datatableMap.insert(QString("figure1"), datatable_figure1);

    //figure 2
    mwArray* f2_E[3];
    f2_E[0] = &matrix_f2_E1;
    f2_E[1] = &matrix_f2_E2;
    f2_E[2] = &matrix_f2_E3;
    listCount = 3;
    valueCount = 81;
    DataTable datatable_figure2;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f2_x.Get(1, j+1), f2_E[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure2 << dataList;
    }
    datatableMap.insert(QString("figure2"), datatable_figure2);

    //figure 3
    mwArray* f3_p[4];
    f3_p[0] = &matrix_f3_HH1;
    f3_p[1] = &matrix_f3_HH2;
    f3_p[2] = &matrix_f3_HH3;
    f3_p[3] = &matrix_f3_LH1;
    listCount = 4;
    valueCount = 81;
    DataTable datatable_figure3;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f3_x.Get(1, j+1), f3_p[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure3 << dataList;
        //qDebug() << "list:";
        //qDebug() << dataList;
    }
    datatableMap.insert(QString("figure3"), datatable_figure3);

    //figure 4
    mwArray* f4_p[1];
    f4_p[0] = &matrix_f4_gai;
    listCount = 1;
    valueCount = 301;
    DataTable datatable_figure4;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f4_x.Get(1, j+1), f4_p[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure4 << dataList;
        //qDebug() << "list:";
        //qDebug() << dataList;
    }
    datatableMap.insert(QString("figure4"), datatable_figure4);

    //figure 5
    mwArray* f5_p[1];
    f5_p[0] = &matrix_f5_ref;
    listCount = 1;
    valueCount = 301;
    DataTable datatable_figure5;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f5_x.Get(1, j+1), f5_p[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure5 << dataList;
        //qDebug() << "list:";
        //qDebug() << dataList;
    }
    datatableMap.insert(QString("figure5"), datatable_figure5);

    //figure 6
    mwSize elems = matrix_f6_x.NumberOfElements();
    mwArray* f6_p[2];
    f6_p[0] = &matrix_f6_YYy;
    f6_p[1] = &matrix_f6_mm1;  //pass by a single number
    listCount = 2;
    //valueCount = 9252;
    valueCount = (int)elems;

    DataTable datatable_figure6;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        if(i < listCount-1){
            for (int j(0); j < valueCount; j++) {
                QPointF value(matrix_f6_x.Get(1, j+1), f6_p[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
                QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
                dataList << Data(value, label);
            }
        }
        else
        {
            //last datalist store a single number: matrix_f6_mm1
            for (int j(0); j < 1; j++) {  //j<1, indicate a single number
                QPointF value(0, f6_p[i]->Get(1, j+1)); //first param is not use. value.x() and value .y() can get two values
                QString label = "Slice " + QString::number(i) + ":" + "matrix_f6_mm1";
                dataList << Data(value, label);
            }
        }
        datatable_figure6 << dataList;
    }
    datatableMap.insert(QString("figure6"), datatable_figure6);

    //figure7
    mwArray* f7_p[1];
    f7_p[0] = &matrix_f7_TT;
    listCount = 1;
    valueCount = 301;
    DataTable datatable_figure7;
    for (int i(0); i < listCount; i++) {
        DataList dataList;
        for (int j(0); j < valueCount; j++) {
            QPointF value(matrix_f7_x.Get(1, j+1), f7_p[i]->Get(1, j+1)); //first cols first element, index start from 1. Get(1,2) means first cols 2nd elem, it's actually the first row 2nd elem
            QString label = "Slice " + QString::number(i) + ":" + QString::number(j);
            dataList << Data(value, label);
        }
        datatable_figure7 << dataList;
    }
    datatableMap.insert(QString("figure7"), datatable_figure7);

    return datatableMap;
}
