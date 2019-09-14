#ifndef RUNMANAGER_H
#define RUNMANAGER_H

#include <QTextEdit>    //文本
#include <QFileDialog>

class MainWindow;
class FileManager;

class RunManager
{
public:
    RunManager(MainWindow *parent,FileManager *fileManager);
    void runAction();
    void compile();
    void compileAndRun();
private:
    void precomp();
    MainWindow *mainWindow;
    FileManager *fileManager;
};
#endif // RUNMANAGER_H
