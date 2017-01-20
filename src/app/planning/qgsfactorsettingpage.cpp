#include "qgsfactorsettingpage.h"
#include <QLabel>
#include <QMap>

QgsFactorSettingPage::QgsFactorSettingPage(QWidget *parent) :
    QWizardPage(parent)
{
	setWindowTitle(QString::fromLocal8Bit("因子权重设置"));

	QMap<QString,QString> data;
	data.insert(QString::fromLocal8Bit("高程"),QString::number(0.15));
	data.insert(QString::fromLocal8Bit("坡度"),QString::number(0.13));
	data.insert(QString::fromLocal8Bit("地质灾害"),QString::number(0.13));
	data.insert(QString::fromLocal8Bit("植被"),QString::number(0.17));
	data.insert(QString::fromLocal8Bit("水域"),QString::number(0.10));
	data.insert(QString::fromLocal8Bit("土壤"),QString::number(0.17));
	data.insert(QString::fromLocal8Bit("人口"),QString::number(0.15));

	QStringList heads;
	heads<<QString::fromLocal8Bit("因子")<<QString::fromLocal8Bit("权重");

	mSettingWidget = new QgsSettingWidget(heads,data);
	layout = new QGridLayout;
	layout->addWidget(mSettingWidget);
	setLayout(layout);
}

QgsFactorSettingPage::~QgsFactorSettingPage()
{
	delete mSettingWidget;
	delete layout;
}
QMap<QString,QString> QgsFactorSettingPage::getTableDate()
{
	QMap<QString,QString> maps;
	
	QTableWidget *tableWidget = mSettingWidget->getTableWidget();
	//int cols = tableWidget->columnCount();
	int rows = tableWidget->rowCount();
	for (int i = 0;i<rows;i++)
	{		
		maps.insert(tableWidget->item(i,0)->text(),tableWidget->item(i,1)->text());
	}
	return maps;
}
QStringList QgsFactorSettingPage::getFactors()
{
	QStringList factors;

	QTableWidget *tableWidget = mSettingWidget->getTableWidget();
	int cols = tableWidget->columnCount();
	int rows = tableWidget->rowCount();
	for (int i = 0;i<rows;i++)
	{		
		factors<<tableWidget->item(i,0)->text();
	}
	return factors;

}