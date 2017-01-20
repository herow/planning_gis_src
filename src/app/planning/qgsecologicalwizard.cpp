
#include <QFileInfo>
#include <QProgressDialog>
#include "qgsecologicalwizard.h"
#include "qgsapplication.h"
#include "qgsrastercalculator.h"
#include "qgsrasterlayer.h"
#include "qgisapp.h"

QgsEcologicalWizard::QgsEcologicalWizard(QWidget *parent) :
    QWizard(parent)
{
    mFactorsSetting = new QgsFactorSettingPage();
	mFilesSetting = new QgsFileSelectPage();

    setPage(QgsEcologicalWizard::factors,mFactorsSetting);
	setPage(QgsEcologicalWizard::files,mFilesSetting);
    //setPage(QgsEcologicalWizard::scores,mScoresSetting);

    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    setWizardStyle( QWizard::ModernStyle );
	setWindowTitle( tr("factors"));

    setOption( QWizard::NoBackButtonOnStartPage );
    //setOption( QWizard::NoBackButtonOnLastPage );
	setOption(QWizard::NoCancelButton);
	
 
    setTitleFormat(Qt::RichText);
    setSubTitleFormat(Qt::RichText);
	setButtonText(QWizard::BackButton,QString::fromLocal8Bit("上一步"));
    setButtonText(QWizard::NextButton, QString::fromLocal8Bit("下一步>"));
	//setButtonText(QWizard::CancelButton,QString::fromLocal8Bit("取消"));
	setButtonText(QWizard::FinishButton,QString::fromLocal8Bit("开始计算"));

	setWindowTitle(QString::fromLocal8Bit("生态适宜性评价"));
}

QgsEcologicalWizard::~QgsEcologicalWizard()
{
	/* delete mFactorsSetting;
	delete mScoresSetting;*/
}

void QgsEcologicalWizard::accept()
{
	//获取各因子权重
	QMap<QString,QString> factorMap = mFactorsSetting->getTableDate();
	QStringList factorList = mFactorsSetting->getFactors();
	//获取文件路径
	QMap<QString,QString> filesMap = mFilesSetting->getTableData();
	//获取文件保存路径
	QString savePath = mFilesSetting->getSavePath();
	//栅格计算

	QString formatStr;
	QVector<QgsRasterCalculatorEntry> entries;
	QgsRectangle rect;
	int cols=0,rows=0;
	bool firstLayer = true;
	foreach(QString factor,factorList)
	{
		QFileInfo fileInfo(filesMap.value(factor));
		QString rasterdir = fileInfo.filePath();
		QString rasterbasename = fileInfo.completeBaseName();
		QgsRasterLayer* rlayer = new  QgsRasterLayer( rasterdir, rasterbasename );	
		if ( rlayer && rlayer->dataProvider() && rlayer->dataProvider()->name() == "gdal" )
		{
			QgsRasterCalculatorEntry entry;
			entry.raster = rlayer;
			entry.bandNumber = 1;
			entry.ref = rlayer->name();
			entries.push_back(entry);
			if ( firstLayer )
			{
				rect = rlayer->extent();
				cols = rlayer->width();
				rows = rlayer->height();
				formatStr.append("\"" + entry.ref + "\" * " + factorMap.value(factor));
				firstLayer = false;
			}
			else
			{
				formatStr.append("+ \"" + entry.ref + "\" * "+ factorMap.value(factor));
			}
		}
	}

	QgsRasterCalculator rc( formatStr, savePath,"GTiff", rect, cols, rows, entries);
	QProgressDialog p( QString::fromLocal8Bit("计算中..."), QString::fromLocal8Bit("取消"), 0, 0 );
	p.setWindowTitle(QString::fromLocal8Bit("生态适宜性评价"));
	p.setWindowModality( Qt::WindowModal );
	if ( rc.processCalculation( &p ) == 0 )
	{
		QgisApp::instance()->addRasterLayer(savePath,QFileInfo(savePath).baseName());
	}

	//QDialog::accept();
}