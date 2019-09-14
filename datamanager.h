#ifndef DATAMANAGER_H
#define DATAMANAGER_H

#include "line.h"

#include <QStringList>

class MainWindow;
const bool MAX=1010;

class DataManager
{
private:
    std::list<Line> lines;
    int lineNumber;

    MainWindow *mainWindow;

    int tagOfAnnotation=0;
    int tagOfDouble=0;
    int tagOfSingle=0;

    void findNormal(QString str,QString data,QString annotation,int count);
    void findDouble(QString str);
    void findAnnotation(QString str);
public:
    DataManager(MainWindow *parent);
    void saveData();
    QStringList getData();
    QStringList getDataAndAnnotation();//每个节点均为对应行的data+annotation
};

#endif // DATAMANAGER_H
