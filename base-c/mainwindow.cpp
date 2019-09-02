#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "helpmanager.h"
#include "globalres.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GlobalRes::setPMainWindow(this);
    GlobalRes::setPFileManager(new FileManager());

    createActions();
    createDockWindows();
    createStatusBar();

    setWindowTitle("Base-C");


}

MainWindow::~MainWindow()
{
    delete ui;
    delete GlobalRes::getPFileManager();
}


void MainWindow::on_actionSave_As_triggered()
{
    GlobalRes::getPFileManager()->saveAs();
}

void MainWindow::on_actionCreate_triggered()
{
    GlobalRes::getPFileManager()->newFile();
}

void MainWindow::on_actionOpen_triggered()
{
    GlobalRes::getPFileManager()->open();
}

void MainWindow::on_actionSave_triggered()
{
    GlobalRes::getPFileManager()->save();
}

void MainWindow::on_actionClose_triggered()
{
    GlobalRes::getPFileManager()->close();
}

void MainWindow::on_actionCopy_triggered()
{

}

void MainWindow::on_actionCut_triggered()
{

}

void MainWindow::on_actionPaste_triggered()
{

}

void MainWindow::on_actionSelect_All_triggered()
{

}

void MainWindow::on_actionAnnotation_triggered()
{

}

void MainWindow::on_actionUnannotation_triggered()
{

}

void MainWindow::on_actionRun_triggered()
{

}

void MainWindow::on_actionCompile_triggered()
{

}

void MainWindow::on_actionRun_Compile_triggered()
{

}

void MainWindow::on_actionStop_triggered()
{

}

void MainWindow::on_actionAbout_Base_C_triggered()
{
    HelpManager::aboutBaseC();
}

void MainWindow::on_actionMotto_of_the_day_triggered()
{
    HelpManager::showMotto();
}

void MainWindow::on_actionAbout_us_triggered()
{
    HelpManager::aboutUs();
}

void MainWindow::createDockWindows()
{
    QDockWidget *dock=new QDockWidget("Console",this);
    dock->setAllowedAreas(Qt::BottomDockWidgetArea);
    addDockWidget(Qt::BottomDockWidgetArea,dock);
    dock->setFixedHeight(250);

    windowsMenu->addAction(dock->toggleViewAction());

}

void MainWindow::createActions()
{
    QMenu *fileMenu=menuBar()->addMenu("&File");

    QAction *createAction=new QAction("&Create",this);
    createAction->setStatusTip("Create a file");
    connect(createAction,&QAction::triggered,this,&MainWindow::on_actionCreate_triggered);
    fileMenu->addAction(createAction);

    QAction *openAction=new QAction("&Open",this);
    openAction->setStatusTip("Open a file");
    connect(openAction,&QAction::triggered,this,&MainWindow::on_actionOpen_triggered);
    fileMenu->addAction(openAction);

    QAction *saveAction=new QAction("&Save",this);
    openAction->setStatusTip("Save a file");
    connect(saveAction,&QAction::triggered,this,&MainWindow::on_actionSave_triggered);
    fileMenu->addAction(saveAction);

    QAction *saveAsAction=new QAction("&Save As",this);
    saveAsAction->setStatusTip("Save a file as ...");
    connect(saveAction,&QAction::triggered,this,&MainWindow::on_actionSave_As_triggered);
    fileMenu->addAction(saveAsAction);

    QAction *closeAction=new QAction("&Close",this);
    closeAction->setStatusTip("Close a file");
    connect(closeAction,&QAction::triggered,this,&MainWindow::on_actionClose_triggered);
    fileMenu->addAction(closeAction);


    QMenu *editMenu=menuBar()->addMenu("&Edit");

    QAction *copyAction=new QAction("&Copy",this);
    copyAction->setStatusTip("Copy");
    connect(copyAction,&QAction::triggered,this,&MainWindow::on_actionCopy_triggered);
    editMenu->addAction(copyAction);

    QAction *cutAction=new QAction("&Cut",this);
    cutAction->setStatusTip("Cut");
    connect(cutAction,&QAction::triggered,this,&MainWindow::on_actionCut_triggered);
    editMenu->addAction(cutAction);

    QAction *pasteAction=new QAction("&Paste",this);
    pasteAction->setStatusTip("Paste");
    connect(pasteAction,&QAction::triggered,this,&MainWindow::on_actionPaste_triggered);
    editMenu->addAction(pasteAction);

    QAction *selectAllAction=new QAction("&Select All",this);
    selectAllAction->setStatusTip("Select All");
    connect(selectAllAction,&QAction::triggered,this,&MainWindow::on_actionSelect_All_triggered);
    editMenu->addAction(selectAllAction);

    QAction *annotationAction=new QAction("&Annotation",this);
    annotationAction->setStatusTip("Annotation");
    connect(annotationAction,&QAction::triggered,this,&MainWindow::on_actionAnnotation_triggered);
    editMenu->addAction(annotationAction);

    QAction *unannotationAction=new QAction("&Unannotation",this);
    unannotationAction->setStatusTip("Unannotation");
    connect(unannotationAction,&QAction::triggered,this,&MainWindow::on_actionUnannotation_triggered);
    editMenu->addAction(unannotationAction);


    QMenu *compileMenu=menuBar()->addMenu("&Compile");

    QAction *runAction=compileMenu->addAction("&Run");
    runAction->setStatusTip("Run the file compiled last time");
    connect(runAction,&QAction::triggered,this,&MainWindow::on_actionRun_triggered);
    compileMenu->addAction(runAction);

    QAction *compileAction=compileMenu->addAction("&Compile");
    compileAction->setStatusTip("Compile current file");
    connect(compileAction,&QAction::triggered,this,&MainWindow::on_actionCompile_triggered);
    compileMenu->addAction(compileAction);

    QAction *runAndCompileAction=compileMenu->addAction("&Run&&Compile");
    runAndCompileAction->setStatusTip("Compile and run current file");
    connect(runAndCompileAction,&QAction::triggered,this,&MainWindow::on_actionRun_Compile_triggered);
    compileMenu->addAction(runAndCompileAction);

    QAction *stopAction=compileMenu->addAction("&Stop");
    stopAction->setStatusTip("stop to run current file");
    connect(stopAction,&QAction::triggered,this,&MainWindow::on_actionStop_triggered);
    compileMenu->addAction(stopAction);


    windowsMenu=menuBar()->addMenu("&Windows");


    QMenu *helpMenu=menuBar()->addMenu("&Help");

    QAction *aboutBaseCAction=helpMenu->addAction("&About Base-C");
    aboutBaseCAction->setStatusTip("information about base-c");
    connect(aboutBaseCAction,&QAction::triggered,this,&MainWindow::on_actionAbout_Base_C_triggered);
    helpMenu->addAction(aboutBaseCAction);

    QAction *mottoOfTheDayAction=helpMenu->addAction("&Motto of the day");
    mottoOfTheDayAction->setStatusTip("motto of the day");
    connect(mottoOfTheDayAction,&QAction::triggered,this,&MainWindow::on_actionMotto_of_the_day_triggered);
    helpMenu->addAction(mottoOfTheDayAction);

    QAction *aboutUsAction=helpMenu->addAction("&About us");
    aboutUsAction->setStatusTip("information about developers");
    connect(aboutUsAction,&QAction::triggered,this,&MainWindow::on_actionAbout_us_triggered);
    helpMenu->addAction(aboutUsAction);



}

void MainWindow::createStatusBar()
{
    statusBar()->showMessage("Ready");
}

