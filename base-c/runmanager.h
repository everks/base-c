#ifndef RUNMANAGER_H
#define RUNMANAGER_H

#include <QTextEdit>    //文本
#include <QFileDialog>

class RunManager
{
public:
    RunManager();
    void runAction();
    void compile();
    void compileAndRun();
private:
    void precomp();
};
#endif // RUNMANAGER_H
