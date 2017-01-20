#include "kongxinstatus.h"
#include "ui_kongxinstatus.h"

KongXinStatus::KongXinStatus(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::KongXinStatus)
{
    ui->setupUi(this);

}

KongXinStatus::~KongXinStatus()
{
    delete ui;
}
