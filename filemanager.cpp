#include<stdio.h>
#include "filemanager.h"
#include "mainwindow.h"
#include <QMenu>        //加入菜单
#include <QMenuBar>     //加入菜单栏
#include <QAction>      //加入菜单栏
#include <QFileDialog>


QString FileManager::getFileName() const
{
    return fileName;
}

void FileManager::setFileName(const QString &value)
{
    fileName = value;
}

FileManager::FileManager(MainWindow *parent){
    mainWindow=parent;

    this->fileName="";
}

FileManager::~FileManager()
{

}
bool FileManager::open(){
    //打开文件
    fileName = QFileDialog::getOpenFileName(mainWindow,"open");
    if(fileName.isEmpty())
        return false;
    FILE *p=fopen(fileName.toStdString().data(),"r");
    if(p==nullptr)
        return false;
    //建立TextEdit窗口
    mainWindow->createTextEdit();
    QString str;
    while (!feof(p)) {
        char buf[1024]={0};
        fgets(buf,sizeof(buf),p);
        str +=buf;
    }
    fclose(p);
    mainWindow->getTextEdit()->setPlainText(str);
    return true;
}
void FileManager::close(){
    mainWindow->deleteTextEdit();
}
bool FileManager::newFile(){
    fileName="";
    mainWindow->createTextEdit();
    //mainWindow->setTextEdit(text);
    return true;
}
bool FileManager::save(){
    if(fileName.isEmpty())
        fileName=QFileDialog::getSaveFileName(mainWindow,"保存文件");
    if(!fileName.isEmpty()){
        FILE *p=fopen(fileName.toStdString().data(),"w");
        if(p==nullptr)
            return false;
        QString str = mainWindow->getTextEdit()->toPlainText();
        fputs(str.toStdString().data(),p);
        fclose(p);
    }
    return true;
}
bool FileManager::saveAs(){
    fileName=QFileDialog::getSaveFileName(mainWindow,"保存文件");
    if(fileName.isEmpty())
        return false;
    else{
        FILE *p=fopen(fileName.toStdString().data(),"w");
        if(p==nullptr)
            return false;
        QString str=mainWindow->getTextEdit()->toPlainText();
        fputs(str.toStdString().data(),p);
        fclose(p);
    }
    return true;
}

