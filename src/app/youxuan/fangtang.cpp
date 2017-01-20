#include "fangtang.h"
#include "ui_fangtang.h"
#include "qsqlquerymodel.h"

fangtang::fangtang(QSqlQueryModel *model,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::fangtang)
{
    setAttribute(Qt::WA_DeleteOnClose);
    ui->setupUi(this);
    m_model=model;
    ui->tableViewCaption->setModel(m_model);
    ui->tableViewCaption->hideColumn(0);
    ui->tableViewCaption->hideColumn(1);
    ui->tableViewCaption->hideColumn(3);
    ui->tableViewCaption->horizontalHeader()->hide();
	ui->tableViewCaption->resizeColumnsToContents();
    ui->tableViewCaption->selectRow(0);
    QModelIndex detailIndex=m_model->index(0 ,3);

    ui->textEdit->setText(m_model->data(detailIndex, Qt::EditRole).toString());

    connect(ui->tableViewCaption, SIGNAL(clicked(QModelIndex)), this, SLOT(showDetail(QModelIndex)));
}

fangtang::~fangtang()
{
    delete ui;
   // delete m_model;
}
void fangtang::showDetail(QModelIndex index) {
    QModelIndex detailIndex=m_model->index(index.row() ,index.column()+1);

    ui->textEdit->setText(index.model()->data(detailIndex, Qt::EditRole).toString());
}
