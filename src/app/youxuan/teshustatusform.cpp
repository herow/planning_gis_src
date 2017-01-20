#include "teshustatusform.h"
#include "ui_teshustatusform.h"

TeShuStatusForm::TeShuStatusForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TeShuStatusForm)
{
    ui->setupUi(this);
}

TeShuStatusForm::~TeShuStatusForm()
{
    delete ui;
}
