#include "youxuanform.h"
#include "ui_youxuanform.h"

YouxuanForm::YouxuanForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::YouxuanForm)
{
    ui->setupUi(this);
}

YouxuanForm::~YouxuanForm()
{
    delete ui;
}
