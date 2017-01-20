#include <QCloseEvent>
#include "wenti_celueform.h"
#include "ui_wenti_celueform.h"
#include "horizontal_proxy_model.h"
#include "qdatawidgetmapper.h"
#include "qsqltablemodel.h"
WenTi_CeLueForm::WenTi_CeLueForm(QSqlTableModel *model,QSqlTableModel *modelPro_Strategy,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::WenTi_CeLueForm)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    Horizontal_proxy_model* proxy_model = new Horizontal_proxy_model();
    proxy_model->setSourceModel((QAbstractItemModel *)model);
    ui->tableView->setModel(proxy_model);
	ui->tableView->horizontalHeader()->hide();
	ui->tableView->resizeColumnsToContents();
    mapper = new QDataWidgetMapper(this);
    mapper->setSubmitPolicy(QDataWidgetMapper::AutoSubmit);
    mapper->setModel((QAbstractItemModel *)modelPro_Strategy);

    mapper->addMapping(ui->textEditProblem, 2);
    mapper->addMapping(ui->textEditStrategy, 3);
    mapper->toFirst();
    connect( ui->btn_close, SIGNAL(clicked()), this, SLOT( close() ) );
    connect( ui->btn_save, SIGNAL(clicked()), this, SLOT( save()) );
}

WenTi_CeLueForm::~WenTi_CeLueForm()
{
    delete ui;
    delete mapper;
}
void WenTi_CeLueForm::closeEvent(QCloseEvent *event)
{

    event->accept();
}
void WenTi_CeLueForm::save()
{
    mapper->submit();
}
