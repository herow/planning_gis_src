#include "weiguanxingtai.h"
#include "ui_weiguanxingtai.h"
#include "qgsapplication.h"
#include "fileinput.h"
#include <QSettings>
#include <QFileDialog>
#include <QFileInfo>

weiguanxingtai::weiguanxingtai(QWidget *parent) :
    ui(new Ui::weiguanxingtai)
{
    ui->setupUi(this);

	connect(ui->nextBtn,SIGNAL(clicked()),this,SLOT(accept()));
	connect(ui->cancelBtn,SIGNAL(clicked()),this,SLOT(reject()));
	connect(ui->chooseBtn,SIGNAL(clicked()),this,SLOT(path()));
}

weiguanxingtai::~weiguanxingtai()
{
    delete ui;
}
void weiguanxingtai::accept()
{
	QString title = ui->titleEdit->text();
	QString type = ui->typeEdit->text();
	QString description = ui->desEdit->toPlainText();
	QString path = ui->pathEdit->text();

	QFileInfo fi(path);
	QString fileName = fi.fileName();
	fileName = randomFileName(fileName);

	QString des = QgsApplication::pkgDataPath()+ (QString("//data//images//microdesign//")).append(fileName);
	fileCopy(path,des);

	QString sql( QString::fromLocal8Bit("INSERT INTO `微观形态设计` VALUES ('%1','%2','%3','%4')").arg(title).arg(type).arg(description).arg((QString("images//microdesign//")).append(fileName)));

	execSQL( QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\db\\test.db"),sql);
	QDialog::accept();
}

void weiguanxingtai::reject()
{
	QDialog::reject();
}

void weiguanxingtai::path()
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