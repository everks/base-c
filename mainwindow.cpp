#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpmanager.h"
#include <QtWidgets>
#include <QAbstractItemModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    completer(0)
{
    ui->setupUi(this);

    //初始化成员变量
    textEdit=nullptr;

    //创建管理类
    fileManager=new FileManager(this);
    runManager=new RunManager(this,fileManager);
    dataManager=new DataManager(this);


    setToolButtonStyle(Qt::ToolButtonFollowStyle);
    createActions();
    createDockWindows();
    createStatusBar();


    //设置代码补全
    completer=new QCompleter(this);
    completer->setModel(modelFromFile(":/resources/wordlist.txt"));
    completer->setModelSorting(QCompleter::CaseInsensitivelySortedModel);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    completer->setWrapAround(false);


    setWindowTitle("Base-C");


}

MainWindow::~MainWindow()
{
    delete ui;
    delete fileManager;
    delete runManager;
    delete dataManager;
}


void MainWindow::createTextEdit()
{
    if(textEdit!=nullptr){
        textEdit->clear();
    }else{
        textEdit=new TextEdit;
        textEdit->setCompleter(completer);
        setCentralWidget(textEdit);
        highlighter=new Highlighter(textEdit->document());
    }
}

void MainWindow::deleteTextEdit()
{
    if(textEdit!=nullptr){
        delete textEdit;
        textEdit=nullptr;
        setCentralWidget(textEdit);
    }
}






void MainWindow::actionCreate_triggered()
{
    fileManager->newFile();
}

void MainWindow::actionOpen_triggered()
{
    fileManager->open();
}

void MainWindow::actionSave_triggered()
{
    if(textEdit==nullptr)
        return;
    if(textEdit->getHasAnnotation()){
        dataManager->saveData();
        QStringList list=dataManager->getData();

        fileManager->save();
    }
}

void MainWindow::actionSave_As_triggered()
{
    if(textEdit==nullptr)
        return;
    if(textEdit->getHasAnnotation()){
        dataManager->saveData();
        QStringList list=dataManager->getData();

        fileManager->saveAs();
    }
}

void MainWindow::actionClose_triggered()
{
    fileManager->close();
}


void MainWindow::actionUndo_triggered()
{
    if(textEdit==nullptr)
        return;
    if(textEdit->isReadOnly())
        return;
    textEdit->undo();
}

void MainWindow::actionRedo_triggered()
{
    if(textEdit==nullptr)
        return;
    if(textEdit->isReadOnly())
        return;
    textEdit->redo();
}

void MainWindow::actionCopy_triggered()
{
    if(textEdit==nullptr)
        return;
    textEdit->copy();
}

void MainWindow::actionCut_triggered()
{
    if(textEdit==nullptr)
        return;
    textEdit->cut();
}

void MainWindow::actionPaste_triggered()
{
    if(textEdit==nullptr)
        return;
    textEdit->paste();
}

void MainWindow::actionSelect_All_triggered()
{
    if(textEdit==nullptr)
        return;
    textEdit->selectAll();
}

void MainWindow::actionAnnotation_triggered()
{
    if(textEdit==nullptr)
        return;

    actionSave_triggered();

    textEdit->setHasAnnotation(true);
    textEdit->clear();
    QStringList list=dataManager->getDataAndAnnotation();
    foreach (const auto& line, list) {
        textEdit->appendPlainText(line);
    }
    textEdit->setReadOnly(false);
}

void MainWindow::actionUnannotation_triggered()
{
    if(textEdit==nullptr)
        return;

    actionSave_triggered();

    textEdit->setHasAnnotation(false);
    textEdit->clear();
    QStringList list=dataManager->getData();
    foreach (const auto& line, list) {
        textEdit->appendPlainText(line);
    }
    textEdit->setReadOnly(true);
}

void MainWindow::actionRun_triggered()
{
    if(textEdit==nullptr)
        return;
    runManager->runAction();
}

void MainWindow::actionCompile_triggered()
{
    if(textEdit==nullptr)
        return;
    runManager->compile();
}

void MainWindow::actionRun_Compile_triggered()
{
    if(textEdit==nullptr)
        return;
    runManager->compileAndRun();
}

void MainWindow::actionAbout_Base_C_triggered()
{
    HelpManager::getInstance()->aboutBaseC();
}


void MainWindow::actionAbout_us_triggered()
{
    HelpManager::getInstance()->aboutUs();
}

void MainWindow::createDockWindows()
{
    dock=new QDockWidget("Console",this);
    dock->setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea,dock);
    dock->setFixedHeight(250);

    windowsMenu->addAction(dock->toggleViewAction());

}

void MainWindow::updateDockWindows(QStringList list)
{
    consoleList=new QListWidget(dock);
    consoleList->addItems(list);
    dock->setWidget(consoleList);

}

void MainWindow::createActions()
{
    QMenu *fileMenu=menuBar()->addMenu("&File");
    QToolBar *fileTb=addToolBar("File Actions");

    const QIcon createIcon=QIcon::fromTheme("create-file",QIcon(rsrcPath+"/filenew.png"));
    QAction *createAction=new QAction(createIcon,"&Create",this);
    createAction->setStatusTip("Create a file");
    connect(createAction,&QAction::triggered,this,&MainWindow::actionCreate_triggered);
    fileMenu->addAction(createAction);
    fileTb->addAction(createAction);
    createAction->setShortcut(QKeySequence::New);

    const QIcon openIcon=QIcon::fromTheme("open-file",QIcon(rsrcPath+"/fileopen.png"));
    QAction *openAction=new QAction(openIcon,"&Open",this);
    openAction->setStatusTip("Open a file");
    connect(openAction,&QAction::triggered,this,&MainWindow::actionOpen_triggered);
    fileMenu->addAction(openAction);
    fileTb->addAction(openAction);
    openAction->setShortcut(QKeySequence::Open);

    const QIcon saveIcon=QIcon::fromTheme("save-file",QIcon(rsrcPath+"/filesave.png"));
    QAction *saveAction=new QAction(saveIcon,"&Save",this);
    openAction->setStatusTip("Save a file");
    connect(saveAction,&QAction::triggered,this,&MainWindow::actionSave_triggered);
    fileMenu->addAction(saveAction);
    fileTb->addAction(saveAction);
    saveAction->setShortcut(QKeySequence::Save);

    QAction *saveAsAction=new QAction("&Save As",this);
    saveAsAction->setStatusTip("Save a file as ...");
    connect(saveAsAction,&QAction::triggered,this,&MainWindow::actionSave_As_triggered);
    fileMenu->addAction(saveAsAction);
    saveAsAction->setShortcut(QKeySequence::SaveAs);

    QAction *closeAction=new QAction("&Close",this);
    closeAction->setStatusTip("Close a file");
    connect(closeAction,&QAction::triggered,this,&MainWindow::actionClose_triggered);
    fileMenu->addAction(closeAction);
    closeAction->setShortcut(QKeySequence::Close);


    QMenu *editMenu=menuBar()->addMenu("&Edit");
    QToolBar *editTb=addToolBar("Edit Actions");

    const QIcon undoIcon=QIcon::fromTheme("undo-edit",QIcon(rsrcPath+"/editundo.png"));
    QAction *undoAction=new QAction(undoIcon,"&Undo",this);
    undoAction->setStatusTip("Undo");
    connect(undoAction,&QAction::triggered,this,&MainWindow::actionUndo_triggered);
    editMenu->addAction(undoAction);
    editTb->addAction(undoAction);
    undoAction->setShortcut(QKeySequence::Undo);

    const QIcon redoIcon=QIcon::fromTheme("redo-edit",QIcon(rsrcPath+"/editredo.png"));
    QAction *redoAction=new QAction(redoIcon,"&Redo",this);
    undoAction->setStatusTip("Redo");
    connect(redoAction,&QAction::triggered,this,&MainWindow::actionRedo_triggered);
    editMenu->addAction(redoAction);
    editTb->addAction(redoAction);
    redoAction->setShortcut(QKeySequence::Redo);

    const QIcon copyIcon=QIcon::fromTheme("copy-edit",QIcon(rsrcPath+"/editcopy.png"));
    QAction *copyAction=new QAction(copyIcon,"&Copy",this);
    copyAction->setStatusTip("Copy");
    connect(copyAction,&QAction::triggered,this,&MainWindow::actionCopy_triggered);
    editMenu->addAction(copyAction);
    editTb->addAction(copyAction);
    copyAction->setShortcut(QKeySequence::Copy);

    const QIcon cutIcon=QIcon::fromTheme("cut-edit",QIcon(rsrcPath+"/editcut.png"));
    QAction *cutAction=new QAction(cutIcon,"&Cut",this);
    cutAction->setStatusTip("Cut");
    connect(cutAction,&QAction::triggered,this,&MainWindow::actionCut_triggered);
    editMenu->addAction(cutAction);
    editTb->addAction(cutAction);
    cutAction->setShortcut(QKeySequence::Cut);

    const QIcon pasteIcon=QIcon::fromTheme("paste-edit",QIcon(rsrcPath+"/editpaste.png"));
    QAction *pasteAction=new QAction(pasteIcon,"&Paste",this);
    pasteAction->setStatusTip("Paste");
    connect(pasteAction,&QAction::triggered,this,&MainWindow::actionPaste_triggered);
    editMenu->addAction(pasteAction);
    editTb->addAction(pasteAction);
    pasteAction->setShortcut(QKeySequence::Paste);

    QAction *selectAllAction=new QAction("&Select All",this);
    selectAllAction->setStatusTip("Select All");
    connect(selectAllAction,&QAction::triggered,this,&MainWindow::actionSelect_All_triggered);
    editMenu->addAction(selectAllAction);
    selectAllAction->setShortcut(QKeySequence::SelectAll);

    QAction *annotationAction=new QAction("&Annotation",this);
    annotationAction->setStatusTip("Annotation");
    connect(annotationAction,&QAction::triggered,this,&MainWindow::actionAnnotation_triggered);
    editMenu->addAction(annotationAction);
    annotationAction->setShortcut(Qt::CTRL+Qt::Key_Q);

    QAction *unannotationAction=new QAction("&Unannotation",this);
    unannotationAction->setStatusTip("Unannotation");
    connect(unannotationAction,&QAction::triggered,this,&MainWindow::actionUnannotation_triggered);
    editMenu->addAction(unannotationAction);
    unannotationAction->setShortcut(Qt::CTRL+Qt::SHIFT+Qt::Key_Q);


    QMenu *compileMenu=menuBar()->addMenu("&Compile");

    QAction *runAction=compileMenu->addAction("&Run");
    runAction->setStatusTip("Run the file compiled last time");
    connect(runAction,&QAction::triggered,this,&MainWindow::actionRun_triggered);
    compileMenu->addAction(runAction);
    runAction->setShortcut(Qt::Key_F10);

    QAction *compileAction=compileMenu->addAction("&Compile");
    compileAction->setStatusTip("Compile current file");
    connect(compileAction,&QAction::triggered,this,&MainWindow::actionCompile_triggered);
    compileMenu->addAction(compileAction);
    compileAction->setShortcut(Qt::Key_F8);

    QAction *runAndCompileAction=compileMenu->addAction("&Run&&Compile");
    runAndCompileAction->setStatusTip("Compile and run current file");
    connect(runAndCompileAction,&QAction::triggered,this,&MainWindow::actionRun_Compile_triggered);
    compileMenu->addAction(runAndCompileAction);
    runAndCompileAction->setShortcut(Qt::Key_F9);


    windowsMenu=menuBar()->addMenu("&Windows");


    QMenu *helpMenu=menuBar()->addMenu("&Help");

    QAction *aboutBaseCAction=helpMenu->addAction("&About Base-C");
    aboutBaseCAction->setStatusTip("information about base-c");
    connect(aboutBaseCAction,&QAction::triggered,this,&MainWindow::actionAbout_Base_C_triggered);
    helpMenu->addAction(aboutBaseCAction);

    QAction *aboutUsAction=helpMenu->addAction("&About us");
    aboutUsAction->setStatusTip("information about developers");
    connect(aboutUsAction,&QAction::triggered,this,&MainWindow::actionAbout_us_triggered);
    helpMenu->addAction(aboutUsAction);



}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage("Ready");
}

TextEdit *MainWindow::getTextEdit() const
{
    return textEdit;
}

void MainWindow::setTextEdit(TextEdit *value)
{
    textEdit = value;
}

const QString MainWindow::rsrcPath=":images";

QAbstractItemModel *MainWindow::modelFromFile(const QString &filename){
    QFile file(filename);
    if(!file.open(QFile::ReadOnly))
        return new QStringListModel(completer);

#ifndef QT_NO_CURSOR
    QApplication::setOverrideCursor(QCursor(Qt::WaitCursor));
#endif
    QStringList words;

    while(!file.atEnd()){
        QByteArray line=file.readLine();
        if(!line.isEmpty())
            words<<line.trimmed();
    }
#ifndef QT_NO_CURSOR
    QApplication::restoreOverrideCursor();
#endif
    return new QStringListModel(words,completer);
}


