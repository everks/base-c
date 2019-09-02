#include "runmanager.h"
#include "globalres.h"



void RunManager::precomp()//预编译
{
    FILE *p = fopen(GlobalRes::getPFileManager()->getFileName().toStdString().data(),"r");
    if(p == NULL) return ;
    QString cmd = GlobalRes::getPFileManager()->getFileName() +".c";
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
//    if (is_changed == true)//在点击编译按钮，如果文本内容发生变化，就自动保存
//    {
//        save();
//    }
    precomp();
    QString cmd;
    const char *s = GlobalRes::getPFileManager()->getFileName().toStdString().data();
    cmd.sprintf("gcc -o %s.exe %s.c",s,s);
    system(cmd.toStdString().data());//先编译

    //获取编译结果并输出——暂未完成

    //如何删除那个临时文件呢
    cmd = GlobalRes::getPFileManager()->getFileName().replace("/","\\") + ".c";
    remove(cmd.toStdString().data());


    cmd = GlobalRes::getPFileManager()->getFileName() + ".exe";
    system(cmd.toStdString().data());//再运行
}

void RunManager ::compile()
{
//    if (is_changed == true)//在点击编译按钮，如果文本内容发生变化，就自动保存
//    {
//        save();
//    }
    precomp();
    QString cmd;
    const char *s = GlobalRes::getPFileManager()->getFileName().toStdString().data();
    cmd.sprintf("gcc -o %s.exe %s.c",s,s);
    system(cmd.toStdString().data());//编译

    //获取编译结果并输出——暂未完成

    //如何删除那个临时文件呢
    cmd = GlobalRes::getPFileManager()->getFileName().replace("/","\\") + ".c";
    remove(cmd.toStdString().data());
}

RunManager::RunManager()
{

}

void RunManager ::runAction()
{
    QString cmd;
    cmd = GlobalRes::getPFileManager()->getFileName() + ".exe";
    system(cmd.toStdString().data());
}
