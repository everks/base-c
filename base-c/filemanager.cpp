#include<stdio.h>
#include "filemanager.h"
#include <QMenu>        //加入菜单
#include <QMenuBar>     //加入菜单栏
#include <QAction>      //加入菜单栏
#include <QFileDialog>
#include <globalres.h>


QString FileManager::getFileName() const
{
    return fileName;
}

void FileManager::setFileName(const QString &value)
{
    fileName = value;
}

FileManager::FileManager(){
    mainWindow=GlobalRes::getPMainWindow();
    text=nullptr;
    this->fileName="";
}

FileManager::~FileManager()
{

}
bool FileManager::open(){
    //建立TextEdit窗口
    text = new QTextEdit;
    text->setFontPointSize(14);
    //打开文件
    fileName = QFileDialog::getOpenFileName(mainWindow,"open");
    if(fileName.isEmpty())
        return false;
    mainWindow->setCentralWidget(text);
    FILE *p=fopen(fileName.toStdString().data(),"r");
    if(p==nullptr)
        return false;
    QString str;
    while (!feof(p)) {
        char buf[1024]={0};
        fgets(buf,sizeof(buf),p);
        str +=buf;
    }
    fclose(p);
    text->setText(str);
    return true;
}
void FileManager::close(){
    if(text!=nullptr){
        delete text;
        text=nullptr;
        mainWindow->setCentralWidget(text);
    }
}
bool FileManager::newFile(){
    fileName="";
    if(text!=nullptr)
        close();
    text=new QTextEdit;
    text->setText("");
    mainWindow->setCentralWidget(text);
    return true;
}
bool FileManager::save(){
    if(fileName.isEmpty())
        fileName=QFileDialog::getSaveFileName(mainWindow,"保存文件");
    if(!fileName.isEmpty()){
        FILE *p=fopen(fileName.toStdString().data(),"w");
        if(p==nullptr)
            return false;
        QString str = text->toPlainText();
        fputs(str.toStdString().data(),p);
        fclose(p);
    }
    return true;
}
bool FileManager::saveAs(){
    fileName= QFileDialog::getOpenFileName(mainWindow,"打开");
    if(fileName.isEmpty())
        return false;
    else{
        FILE *p=fopen(fileName.toStdString().data(),"w");
        if(p==nullptr)
            return false;
        QString str=text->toPlainText();
        fputs(str.toStdString().data(),p);
        fclose(p);
    }
    return true;
}
char* FileManager::openMotto(char* buf,size_t size){
    int k;
    int i=0;

    k=rand()%10+1;
    QDir dir("../base-c/motto.txt");
    QString str=dir.absolutePath();
    FILE *p = fopen(str.toStdString().data(),"r");

//    std::string str;
//    FILE *p = fopen(str.toStdString().data(),"r");

    if(p==nullptr)
        return buf;
    while(i<k&&!feof(p)){
        memset(buf,0,size);
        fgets(buf,size,p);
        i++;
    }
    return buf;
}
