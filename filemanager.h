#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QMainWindow>
#include <QTextEdit>    //文本

class MainWindow;

class FileManager
{
private:
    QString fileName;
    MainWindow *mainWindow;
public:
    FileManager(MainWindow *parent);
    ~FileManager();
    bool open();
    void close();
    bool newFile();
    bool save();
    bool saveAs();
    QString getFileName() const;
    void setFileName(const QString &value);
};


#endif // FILEMANAGER_H
