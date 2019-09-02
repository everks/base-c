#include "helpmanager.h"
#include "globalres.h"
#include "filemanager.h"

#include <QtWidgets>

HelpManager::HelpManager()
{

}

bool HelpManager::aboutBaseC()
{
    QMessageBox::about(GlobalRes::getPMainWindow(),("About Base-C"),
                       ("The <b>Application</b> example demonstrates how to "
                          "write modern GUI applications using Qt, with a menu bar, "
                          "toolbars, and a status bar."));
    return true;
}

bool HelpManager::showMotto()
{
    char buf[1024]={0};
    FileManager* fileManager=(new FileManager());
    fileManager->openMotto(buf,sizeof(buf));
    QMessageBox::about(GlobalRes::getPMainWindow(),("Motto of the day"),buf);
    return true;
}

bool HelpManager::aboutUs()
{
    QMessageBox::about(GlobalRes::getPMainWindow(),("About Us"),
                       ("开发者：（以下排名不分先后）\n宋溢，吴杰，周越，郑奇，惠杨阳\n"));
    return true;
}
