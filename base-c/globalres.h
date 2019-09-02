#ifndef GLOBALRES_H
#define GLOBALRES_H


#include "mainwindow.h"
#include "filemanager.h"


class GlobalRes
{
private:
    static MainWindow* pMainWindow;
    static FileManager *pFileManager;
public:
    GlobalRes();

    static MainWindow *getPMainWindow();
    static void setPMainWindow(MainWindow *value);
    static FileManager *getPFileManager();
    static void setPFileManager(FileManager *value);
};



#endif // GLOBALRES_H
