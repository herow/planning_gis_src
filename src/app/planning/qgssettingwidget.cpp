#include <QFile>
#include <QTextStream>

#include "qgssettingwidget.h"

QgsSettingWidget::QgsSettingWidget(QString fileName,QWidget *parent) : QWidget(parent)
{
	this->setupUi(this);
	setTable(fileName);
	connect( mAddBtn, SIGNAL(clicked()), this, SLOT(addRow()));
	connect( mDelBtn, SIGNAL(clicked()), this, SLOT(delRow()));
	connect( mClearAllBtn, SIGNAL(clicked()), this, SLOT(clearAll()));
}

QgsSettingWidget::QgsSettingWidget(QStringList heads, QMap<QString,QString> data,QWidget *parent): QWidget(parent)
{
	this->setupUi(this);
	mTableWidget->setColumnCount(heads.count()); 
	mTableWidget->setHorizontalHeaderLabels(heads);
	mTableWidget->setRowCount(data.size()); 
	QMap<QString,QString>::iterator it;
	int i =0;
	for(it=data.begin();it!=data.end();++it)
	{
		mTableWidget->setItem(i,0,new QTableWidgetItem(it.key()));
		mTableWidget->setItem(i,1,new QTableWidgetItem(it.value()));
		i++;
	}
	//mTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	mTableWidget->resizeColumnsToContents();
	mTableWidget->resizeRowsToContents();
	mTableWidget->setColumnWidth(0,150);
	mTableWidget->setColumnWidth(1,200);

	connect( mAddBtn, SIGNAL(clicked()), this, SLOT(addRow()));
	connect( mDelBtn, SIGNAL(clicked()), this, SLOT(delRow()));
	connect( mClearAllBtn, SIGNAL(clicked()), this, SLOT(clearAll()));
}



void QgsSettingWidget::setTable(QString fileName)
{
    QFile file(fileName);
    if(file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString line = stream.readLine();
        QStringList heads = line.split(" ");
		mTableWidget->setColumnCount(heads.count()); 
        mTableWidget->setHorizontalHeaderLabels(heads);
        int n = 0;
        while ( !stream.atEnd()) {
            line = stream.readLine();
            QStringList rowData = line.split(" ");
			mTableWidget->insertRow(n);
            for(int i = 0;i<rowData.count();i++){     
                mTableWidget->setItem(n,i,new QTableWidgetItem(rowData.at(i)));
            }
			n++;
        }
    }
    file.close();
}
void QgsSettingWidget::addRow(){
	mTableWidget->insertRow(mTableWidget->rowCount());
}
void QgsSettingWidget::delRow(){
	int rowIndex = mTableWidget->currentRow();
	if (rowIndex != -1)
	{
		mTableWidget->removeRow(rowIndex);
	}
}
void QgsSettingWidget::clearAll()
{
	mTableWidget->clearContents();
	mTableWidget->setRowCount(0);
}

QMap<QString,QString> QgsSettingWidget::getData()
{
	QMap<QString,QString> maps;
	int cols = mTableWidget->columnCount();
	int rows = mTableWidget->rowCount();
	for (int i = 0;i<rows;i++)
	{		
		maps.insert(mTableWidget->item(i,0)->text(),mTableWidget->item(i,1)->text());
	}
	return maps;
}