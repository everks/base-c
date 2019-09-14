#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "line.h"
#include "textedit.h"
#include "highlighter.h"
#include "filemanager.h"
#include "runmanager.h"
#include "datamanager.h"

#include <QCompleter>
#include <QListWidget>
#include <QMainWindow>
#include <QTextEdit>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createTextEdit();
    void deleteTextEdit();

    TextEdit *getTextEdit() const;
    void setTextEdit(TextEdit *value);

    void updateDockWindows(QStringList list);
private slots:
    void actionSave_As_triggered();

    void actionCreate_triggered();

    void actionOpen_triggered();

    void actionSave_triggered();

    void actionClose_triggered();

    void actionUndo_triggered();

    void actionRedo_triggered();

    void actionCopy_triggered();

    void actionCut_triggered();

    void actionPaste_triggered();

    void actionSelect_All_triggered();

    void actionAnnotation_triggered();

    void actionUnannotation_triggered();

    void actionRun_triggered();

    void actionCompile_triggered();

    void actionRun_Compile_triggered();

    void actionAbout_Base_C_triggered();

    void actionAbout_us_triggered();


private:
    void createDockWindows();
    void createActions();
    void createStatusBar();
    QAbstractItemModel *modelFromFile(const QString& filename);

    Ui::MainWindow *ui;

    QListWidget *consoleList;
    QDockWidget *dock;

    QMenu *windowsMenu;

    QCompleter *completer;
    TextEdit *textEdit;
    Highlighter *highlighter;

    FileManager *fileManager;
    RunManager *runManager;
    DataManager *dataManager;



    static const QString rsrcPath;

};

#endif // MAINWINDOW_H
