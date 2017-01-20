#include "diaochaform.h"
#include "ui_diaochaform.h"

DiaoChaForm::DiaoChaForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DiaoChaForm)
{
    ui->setupUi(this);
}

DiaoChaForm::~DiaoChaForm()
{
    delete ui;
}
