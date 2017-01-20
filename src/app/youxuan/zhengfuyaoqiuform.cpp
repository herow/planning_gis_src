#include "zhengfuyaoqiuform.h"
#include "ui_zhengfuyaoqiuform.h"

ZhengFuYaoqiuForm::ZhengFuYaoqiuForm(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZhengFuYaoqiuForm)
{
    ui->setupUi(this);
}

ZhengFuYaoqiuForm::~ZhengFuYaoqiuForm()
{
    delete ui;
}
