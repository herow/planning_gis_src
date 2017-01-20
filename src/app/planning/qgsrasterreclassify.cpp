#include <QDialogButtonBox>
#include <QLabel>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QFileInfo>
#include <QProgressDialog>

#include "qgisapp.h"
#include "qgsrastercalculator.h"
#include "qgsrasterreclassify.h"

QgsRasterReclassify::QgsRasterReclassify(QString title,QMap<QString,QString>data)
{
	setWindowTitle(title);
	QDialogButtonBox *buttonBox = new QDialogButtonBox(this);
	buttonBox->setStandardButtons(QDialogButtonBox::Ok);
	buttonBox->button(QDialogButtonBox::Ok)->setText(QString::fromLocal8Bit("确定"));
	//buttonBox->button(QDialogButtonBox::Cancel)->setText(QString::fromLocal8Bit("取消"));
	//connect(buttonBox->button(QDialogButtonBox::Cancel), SIGNAL(clicked()), this, SLOT(reject()));
	connect(buttonBox->button(QDialogButtonBox::Ok), SIGNAL(clicked()), this, SLOT(accept()));

	
	QStringList heads;
	heads<<QString::fromLocal8Bit("区间")<<QString::fromLocal8Bit("属性值");
	mQgsSettingWidget = new QgsSettingWidget(heads,data);
	
	mOpenWidget = new SaveWidget(SaveWidget::Open);
	mSaveWidget = new SaveWidget();
	
	
	QGridLayout* gridLayout = new QGridLayout();
	gridLayout->addWidget(mOpenWidget);
	gridLayout->addWidget(mQgsSettingWidget);
	gridLayout->addWidget(mSaveWidget);
	gridLayout->addWidget(buttonBox);
	setLayout(gridLayout);

	resize(500,450);
}

QgsRasterReclassify::~QgsRasterReclassify()
{

}

void QgsRasterReclassify::accept()
{
	//获取各因子权重
	QMap<QString,QString> rangeMap = mQgsSettingWidget->getData();

	QString inputFile = mOpenWidget->getFilePath();
	QString outpuFile = mSaveWidget->getFilePath();


	//栅格计算
	QString formatStr;
	QVector<QgsRasterCalculatorEntry> entries;
	QgsRectangle rect;
	int cols=0,rows=0;
	QFileInfo fileInfo(inputFile);
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
		rect = rlayer->extent();
		cols = rlayer->width();
		rows = rlayer->height();
		
	}
	bool isFirst = true;
	QMap<QString,QString>::iterator it; 
	for ( it = rangeMap.begin(); it != rangeMap.end(); ++it ) {
		QString value = it.value();
		QStringList range =  it.key().split("-");
		if (isFirst)
		{		
			formatStr = QString("(@name@ > ").append(range[0]).append(QString(" AND @name@ <=  ")).append(range[1]).append(QString(" )* ")).append(value);
			isFirst = false;
		}
		else
		{
			formatStr.append(QString(" + (@name@ > ").append(range[0]).append(QString(" AND @name@ <=  ")).append(range[1]).append(QString(" )* ")).append(value));
		}		
	}
	formatStr.replace("@name@","\""+rlayer->name() +"\"");
	qDebug("%s",formatStr);
	QgsRasterCalculator rc( formatStr, outpuFile,"GTiff", rect, cols, rows, entries);
	QProgressDialog p( tr( "Calculating..." ), tr( "Abort..." ), 0, 0 );
	p.setWindowModality( Qt::WindowModal );
	if ( rc.processCalculation( &p ) == 0 )
	{
		QgisApp::instance()->addRasterLayer(outpuFile,QFileInfo(outpuFile).baseName());
	}
	//QDialog::accept();
}

void QgsRasterReclassify::reject()
{
	QDialog::reject();
}