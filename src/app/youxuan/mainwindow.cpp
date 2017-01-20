#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "youxuandockwidget.h"
#include "connection.h"
#include "mainwindow2.h"
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect( ui->youxuanaction, SIGNAL(triggered()), this, SLOT( showWizard() ) );
    connect( ui->microdesign, SIGNAL(triggered()), this, SLOT( showMicroDesign() ) );
    if (!createConnection())
        return  ;
     wizard = new YouXuanDockWidget();
     MicroDesign =new MainWindow2();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::showWizard()
{

    wizard->show();
}
void MainWindow::showMicroDesign()
{
   MicroDesign->show();
}
