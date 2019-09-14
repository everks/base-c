#include "helpmanager.h"
#include "filemanager.h"

#include <QtWidgets>

HelpManager *HelpManager::instance=nullptr;

HelpManager::HelpManager()
{

}

bool HelpManager::aboutBaseC()
{
    QMessageBox::about(nullptr,("About Base-C"),
                       ("The <b>Application</b> example demonstrates how to "
                          "write modern GUI applications using Qt, with a menu bar, "
                          "toolbars, and a status bar."));
    return true;
}

bool HelpManager::aboutUs()
{
    QMessageBox::about(nullptr,("About Us"),
                       ("开发者：（以下排名不分先后）\n宋溢，吴杰，周越，郑奇，惠杨阳\n"));
    return true;
}

HelpManager *HelpManager::getInstance()
{
    if(instance==nullptr)
        instance=new HelpManager();
    return instance;
}

void HelpManager::destory()
{
    if(instance!=nullptr){
        delete instance;
        instance=nullptr;
    }
}
