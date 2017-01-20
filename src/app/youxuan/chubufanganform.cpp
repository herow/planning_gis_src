#include "chubufanganform.h"
#include "ui_chubufanganform.h"
#include <QCloseEvent>
#include "qdatawidgetmapper.h"
#include "qsqltablemodel.h"
#include <QModelIndex>
ChuBuFangAnForm::ChuBuFangAnForm(QSqlTableModel *modelPro_Strategy,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ChuBuFangAnForm)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    connect( ui->btn_generate, SIGNAL(clicked()), this, SLOT( generate() ) );
    connect( ui->btn_save, SIGNAL(clicked()), this, SLOT( save()) );
    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    mapper->setModel((QAbstractItemModel *)modelPro_Strategy);

    mapper->addMapping(ui->textEdit, 4);
    mapper->toFirst();

    model=modelPro_Strategy;

}

ChuBuFangAnForm::~ChuBuFangAnForm()
{
    delete ui;
    delete mapper;

}
void ChuBuFangAnForm::generate()
{
    QModelIndex detailIndex1=model->index(0 ,2);
    QModelIndex detailIndex2=model->index(0 ,3);

    QString str_pro=model->data(detailIndex1, Qt::EditRole).toString();
    QString str_strategy=model->data(detailIndex2, Qt::EditRole).toString();
    str_pro.append("\n");
    str_strategy.append("\n");
    ui->textEdit->setText(str_pro+str_strategy);
}
void ChuBuFangAnForm::save()
{
    mapper->submit();
}
void ChuBuFangAnForm::closeEvent(QCloseEvent *event)
{

    event->accept();
}
