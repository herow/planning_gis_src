#include "cunminyijianform.h"
#include "ui_cunminyijianform.h"

CunMinYIjianForm::CunMinYIjianForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::CunMinYIjianForm)
{
    ui->setupUi(this);
}

CunMinYIjianForm::~CunMinYIjianForm()
{
    delete ui;
}
