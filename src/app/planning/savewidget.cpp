#include <QSettings>
#include <QFileDialog>

#include "savewidget.h"
#include "ui_savewidget.h"

SaveWidget::SaveWidget(Type type,QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SaveWidget)
{
	ui->setupUi(this);
	if (type == SaveWidget::Save)
	{
		connect(ui->mSaveBtn, SIGNAL(clicked()), this, SLOT(setSavePath()));
	}
	else
	{
		ui->label_2->setText(QString::fromLocal8Bit("输入栅格文件"));
		ui->mSaveBtn->setText(QString::fromLocal8Bit("打开"));
		connect(ui->mSaveBtn, SIGNAL(clicked()), this, SLOT(setOpenPath()));
	}
}

SaveWidget::~SaveWidget()
{
    delete ui;
}

void SaveWidget::setSavePath()
{
	QSettings settings;
	QString lastUsedDir = settings.value( "/UI/lastProjectDir", "." ).toString();
	QString fullPath = QFileDialog::getSaveFileName( this,
		QString::fromLocal8Bit("保存文件"),
		lastUsedDir,
		tr( "GeoTiff" ) + " (*.tif)" );
	if ( fullPath.isNull() )
	{
		return ;
	}
	QFileInfo myFI( fullPath );
	QString myPath = myFI.path();
	settings.setValue( "/UI/lastProjectDir", myPath );
	ui->mSaveEdit->setText(fullPath);
}

QString SaveWidget::getFilePath()
{
	return ui->mSaveEdit->text();
}

void SaveWidget::setOpenPath()
{
	QSettings settings;
	QString lastUsedDir = settings.value( "/UI/lastProjectDir", "." ).toString();
	QString fullPath = QFileDialog::getOpenFileName( this,
		QString::fromLocal8Bit("选择文件"),
		lastUsedDir,
		tr( "GeoTiff" ) + " (*.tif)" );
	if ( fullPath.isNull() )
	{
		return;
	}
	QFileInfo myFI( fullPath );
	QString myPath = myFI.path();
	settings.setValue( "/UI/lastProjectDir", myPath );
	ui->mSaveEdit->setText(fullPath);
}