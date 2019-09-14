#include "datamanager.h"
#include "mainwindow.h"


DataManager::DataManager(MainWindow *parent)
{
    mainWindow=parent;
    lineNumber=MAX;
}

void DataManager::saveData()
{
    QString text=mainWindow->getTextEdit()->toPlainText();
    QStringList list=text.split("\n");
    lines.clear();
    lineNumber=list.size();
    for (int var = 0; var < lineNumber; ++var) {
        QString str=list.at(var);
        QString data=nullptr;
        QString annotation=nullptr;
        if(!tagOfAnnotation&&!tagOfDouble){
            findNormal(str,nullptr,nullptr,0);
        }else if(tagOfDouble==1){
            findDouble(str);
        }else{
            findAnnotation(str);
        }
    }
}

QStringList DataManager::getData()
{
    QStringList list;
    foreach (const Line &var, lines) {
        list.append(var.getData());
    }
    return list;
}

QStringList DataManager::getDataAndAnnotation()
{
    QStringList list;
    foreach (const Line &var, lines) {
        list.append(var.getData()+var.getAnnotation());
    }
    return list;
}


void DataManager::findNormal(QString str,QString data,QString annotation,int count)
{
    for (; count<str.length(); ++count) {
        if(str.at(count)=='\"'){
            count++;
            tagOfDouble=1;
            while(str.at(count)!='\"'&&count<str.length()){
                data.append(str.at(count));
                count++;
            }
            if(str[count]=='\"')
                tagOfDouble=0;
        }else if(str.at(count)=='/'&&count>0&&str.at(count-1)=='/'){
            data.remove(data.length()-1,1);
            annotation="//"+str.split("//")[1];
            break;
        }else if(str.at(count)=='*'&&count>0&&str.at(count-1)=='/'){
            count++;
            tagOfAnnotation=1;
            data.remove(data.length()-1,1);
            annotation+="/*";
            while(count<str.length()){
                if(str.at(count)=='/'&&str.at(count-1)=='*'){
                    break;
                }else{
                    annotation.append(str.at(count));
                }
                count++;
            }
            if(count<str.length())
            {
                annotation.append('/');
                tagOfAnnotation=0;
            }
        }else{
            data.append(str.at(count));
        }
    }
    lines.push_back(Line(data,annotation));
}

void DataManager::findDouble(QString str)
{
    QString data=nullptr;
    QString annotation=nullptr;
    for (int count = 0; count < str.length(); ++count) {
        if(str.at(count)=='\"'){
            tagOfDouble=0;
            data.append(str.at(count));
            findNormal(str,data,annotation,count);
            return;
        }else{
            data.append(str.at(count));
        }
    }
    lines.push_back(Line(data,annotation));
}

void DataManager::findAnnotation(QString str)
{
    QString data=nullptr;
    QString annotation=nullptr;
    for (int count = 0; count < str.length(); ++count) {
        if(str.at(count)=='/'&&count>0&&str.at(count-1)=='*'){
            tagOfAnnotation=0;
            annotation.append(str.at(count));
            findNormal(str,data,annotation,++count);
            return;
        }else{
            annotation.append(str.at(count));
        }
    }
    lines.push_back(Line(data,annotation));
}
