#include "finalfanganform.h"
#include "ui_finalfanganform.h"
#include "qsqltablemodel.h"
#include "qdatawidgetmapper.h"
FinalFanganForm::FinalFanganForm(QSqlTableModel *modelPro_Strategy,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::FinalFanganForm)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    connect( ui->btn_generate, SIGNAL(clicked()), this, SLOT( generate() ) );
    connect( ui->btn_save, SIGNAL(clicked()), this, SLOT( save()) );
    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    mapper->setModel((QAbstractItemModel *)modelPro_Strategy);

    mapper->addMapping(ui->textEdit, 5);
    mapper->toFirst();

    model=modelPro_Strategy;
}

FinalFanganForm::~FinalFanganForm()
{
    delete ui;
    delete mapper;
}
void FinalFanganForm::generate()
{
    QModelIndex detailIndex=model->index(0 ,4);
//    QModelIndex detailIndex2=model->index(0 ,3);

//    QString str_pro=model->data(detailIndex1, Qt::EditRole).toString();
    QString str_inistrategy=model->data(detailIndex, Qt::EditRole).toString();
//    str_pro.append("\n");
    str_inistrategy.append("\n");
    ui->textEdit->setText(str_inistrategy);
}
void FinalFanganForm::save()
{
    mapper->submit();
}
