#ifndef HELPMANAGER_H
#define HELPMANAGER_H
#include<string>

class HelpManager
{
private:
    HelpManager();

    static HelpManager* instance;
public:
    static HelpManager* getInstance();
    void destory();
    bool aboutBaseC();
    bool aboutUs();
};
#endif // HELPMANAGER_H
