
#include <QFileDialog>
#include <QSettings>

#include "qgsfilesselectwidget.h"
#include "qgsfileselectbasewidget.h"


QgsFilesSelectWidget::QgsFilesSelectWidget(QStringList heads, QStringList files,QWidget *parent) :
    QWidget(parent)
{
    this->setupUi(this);
	mTableWidget->setColumnCount(heads.count()); 
	mTableWidget->setRowCount(files.count()); 
	mTableWidget->setHorizontalHeaderLabels(heads);
	int i = 0;
	foreach (QString file,files)
	{
		mTableWidget->setItem(i,0,new QTableWidgetItem(file));
		mTableWidget->setCellWidget(i,1,new QgsFileSelectBaseWidget());
		i++;
	}
	mTableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
	mTableWidget->resizeColumnsToContents();
	mTableWidget->resizeRowsToContents();
	mTableWidget->setColumnWidth(0,80);
	mTableWidget->setColumnWidth(1,300);

	connect(mSaveBtn,SIGNAL(clicked()),this,SLOT(save()));
}
QgsFilesSelectWidget::QgsFilesSelectWidget(QWidget *parent) :
QWidget(parent)
{
}

QgsFilesSelectWidget::~QgsFilesSelectWidget()
{
}

QMap<QString,QString> QgsFilesSelectWidget::getTableData()
{
	QMap<QString,QString> maps;
	int cols = mTableWidget->columnCount();
	int rows = mTableWidget->rowCount();
	for (int i = 0;i<rows;i++)
	{		
		QWidget* widget = mTableWidget->cellWidget(i,1);
		QString filename = ((QgsFileSelectBaseWidget*)(widget))->getFileName().trimmed();
		maps.insert(mTableWidget->item(i,0)->text().trimmed(),filename);
	}
	return maps;
}

QString QgsFilesSelectWidget::getSavePath()
{

	return mSaveEdit->text().trimmed();
}

void QgsFilesSelectWidget::save()
{
	mSaveEdit->setText(svePath());
}

QString QgsFilesSelectWidget::svePath()
{
	QSettings settings;
	QString lastUsedDir = settings.value( "/UI/lastProjectDir", "." ).toString();
	QString fullPath = QFileDialog::getSaveFileName( this,
		QString::fromLocal8Bit("±£´æÎÄ¼þ"),
		lastUsedDir,
		tr( "TIF" ) + " (*.tif)" );
	if ( fullPath.isNull() )
	{
		return NULL;
	}
	QFileInfo myFI( fullPath );
	QString myPath = myFI.path();
	settings.setValue( "/UI/lastProjectDir", myPath );
	return fullPath;
}