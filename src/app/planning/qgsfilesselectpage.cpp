#include "qgsfilesselectpage.h"
#include "qgsfactorsettingpage.h"
#include "qgsecologicalwizard.h"

QgsFileSelectPage::QgsFileSelectPage()
{
	QStringList heads,files;
}

QgsFileSelectPage::~QgsFileSelectPage()
{
	delete mFilesSelectWidget;
	delete layout;
}
void QgsFileSelectPage ::initializePage()
{
	QStringList files = ((QgsFactorSettingPage*)(wizard()->page(QgsEcologicalWizard::factors)))->getFactors();
	QStringList heads;
	heads<<QString::fromLocal8Bit("因子") <<QString::fromLocal8Bit("文件");
	mFilesSelectWidget = new QgsFilesSelectWidget(heads,files);
	layout = new QGridLayout;
	layout->addWidget(mFilesSelectWidget);
	setLayout(layout);
}

QMap<QString,QString> QgsFileSelectPage::getTableData()
{
	return mFilesSelectWidget->getTableData();
}