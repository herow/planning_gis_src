#include "shujutujian.h"
#include "ui_shujutujian.h"
#include "qgsapplication.h"
#include "fileinput.h"
#include <QSettings>
#include <QFileDialog>
#include <QFileInfo>

shujutujian::shujutujian(QWidget *parent) :
    ui(new Ui::shujutujian)
{
    ui->setupUi(this);

	connect(ui->nextBtn,SIGNAL(clicked()),this,SLOT(accept()));
	connect(ui->cancelBtn,SIGNAL(clicked()),this,SLOT(reject()));
	connect(ui->chooseBtn,SIGNAL(clicked()),this,SLOT(path()));
}

shujutujian::~shujutujian()
{
    delete ui;
}


void shujutujian::accept()
{
	QString xiang = ui->xiangEdit->text();
	QString cun = ui->cunEdit->text();
	QString title = ui->titleEdit->text();
	QString content = ui->contentEdit->toPlainText();
	QString path = ui->pathEdit->text();

	QFileInfo fi(path);
	QString fileName = fi.fileName();
	fileName = randomFileName(fileName);

	QString des = QgsApplication::pkgDataPath()+ (QString("//data//pic//images//")).append(fileName);
	fileCopy(path,des);
	
	QString sql( QString::fromLocal8Bit("INSERT INTO `Êý¾ÝÍ¼¼þ` VALUES ('%1','%2','%3','%4','%5')").arg(xiang).arg(cun).arg(title).arg(content).arg((QString("images/")).append(fileName)));

	execSQL( QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\db\\test.db"),sql);
	QDialog::accept();
}

void shujutujian::reject()
{
	QDialog::reject();
}

void shujutujian::path()
{
	QSettings settings;
	QString lastUsedDir = settings.value( "/UI/lastDBDir", "." ).toString();
	QString fullPath = QFileDialog::getOpenFileName( this,
		tr( "choose a picture"),
		lastUsedDir,
		tr( "All Files" ) + " (*.* *.*)" );
	if ( fullPath.isNull() )
	{
		return;
	}
	QFileInfo myFI( fullPath );
	QString myPath = myFI.path();
	settings.setValue( "/UI/lastDBDir", myPath );
	ui->pathEdit->setText(fullPath);
}