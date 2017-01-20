#include "mainfrm.h"
#include "ui_mainwindow.h"
#include <QSplitter>
#include <QLineEdit>
#include <QLabel>
#include <tmainwindow.h>
#include <kxcplanningfrm.h>

MainFrm::MainFrm(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QSplitter *splitter = new QSplitter(Qt::Horizontal, this);
    setCentralWidget(splitter);
    splitter->addWidget(new KXCPlanningFrm);
    TMainWindow* mw = new TMainWindow;
    mw->setCentralWidget(new QLabel("123"));
    splitter->addWidget(mw);


}

MainFrm::~MainFrm()
{
    delete ui;
}
