#ifndef GLOBALRES_H
#define GLOBALRES_H


#include "mainwindow.h"
#include "filemanager.h"
#include "runmanager.h"


class GlobalRes
{
private:
    static MainWindow* pMainWindow;
    static FileManager *pFileManager;
    static RunManager *pRunManager;
public:
    GlobalRes();

    static MainWindow *getPMainWindow();
    static void setPMainWindow(MainWindow *value);
    static FileManager *getPFileManager();
    static void setPFileManager(FileManager *value);
    static RunManager *getPRunManager();
    static void setPRunManager(RunManager *value);
};



#endif // GLOBALRES_H
