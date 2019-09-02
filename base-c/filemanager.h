#ifndef FILEMANAGER_H
#define FILEMANAGER_H
#include <QMainWindow>
#include <QTextEdit>    //文本
#include "mainwindow.h"

class FileManager
{
private:
    QString fileName;
    MainWindow *mainWindow;
    QTextEdit *text;
    //bool autoSave();
public:
    FileManager();
    ~FileManager();
    bool open();
    void close();
    bool newFile();
    bool save();
    bool saveAs();
    char* openMotto(char *buf,size_t size);
    QString getFileName() const;
    void setFileName(const QString &value);
};


#endif // FILEMANAGER_H
