#include "mainwindow.h"

void RunManager::precomp()//预编译
{
    FILE *p = fopen(fileManager->getFileName().toStdString().data(),"r");
    if(p == NULL) return ;
    QString cmd = fileManager->getFileName() +".c";
    FILE *p1 = fopen(cmd.toStdString().data(),"w");
    if(p1 == NULL) return ;
    QString str;
    while(!feof(p))
    {
        char buf[1024] = {0};
        fgets(buf,sizeof(buf),p);
        str += buf;
    }
    fputs(str.toStdString().data(),p1);
    fclose(p);
    fclose(p1);
}

void RunManager ::compileAndRun()
{
    compile();
    runAction();
}

void RunManager ::compile()
{
    fileManager->save();

    precomp();
    QString cmd;
    const char *s = fileManager->getFileName().toStdString().data();
    cmd.sprintf("gcc -o %s.exe %s.c 2> %s.txt",s,s,s);
    system(cmd.toStdString().data());//编译

    //获取编译结果并输出——暂未完成
    const char *temp=(fileManager->getFileName()+".txt").toStdString().data();
    FILE *p=fopen(temp,"r");
    if(p==nullptr)
        return;
    QStringList list;
    if(fgetc(p)==EOF){
        list<<"编译成功";
    }else{
        fseek(p,0,SEEK_SET);
        list<<"编译失败";
        while(!feof(p)){
            char buf[1024]={0};
            fgets(buf,sizeof(buf),p);
            list<<buf;
        }
    }
    mainWindow->updateDockWindows(list);

    //如何删除那个临时文件呢
    cmd = fileManager->getFileName().replace("/","\\") + ".c";
    remove(cmd.toStdString().data());
}

RunManager::RunManager(MainWindow *parent,FileManager *fileManager)
{
    this->mainWindow=parent;
    this->fileManager=fileManager;
}

void RunManager ::runAction()
{
    QString cmd;
    cmd = fileManager->getFileName() + ".exe";
    system(cmd.toStdString().data());
}
