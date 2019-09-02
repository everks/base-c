#include "globalres.h"

MainWindow *GlobalRes::getPMainWindow()
{
    return pMainWindow;
}

void GlobalRes::setPMainWindow(MainWindow *value)
{
    pMainWindow = value;
}

FileManager *GlobalRes::getPFileManager()
{
    return pFileManager;
}

void GlobalRes::setPFileManager(FileManager *value)
{
    pFileManager = value;
}

GlobalRes::GlobalRes()
{

}

MainWindow* GlobalRes::pMainWindow=nullptr;
FileManager* GlobalRes::pFileManager=nullptr;
