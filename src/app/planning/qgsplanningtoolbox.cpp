#include <QProcess>

#include "qgsplanningtoolbox.h"
#include "qgsecologicalwizard.h"
#include "qgsrasterreclassify.h"
#include "planningdialog.h"
#include "budianguihua.h"
#include "zhengzhiyinsu.h"
#include "qgsapplication.h"
#include "youxuan/youxuandockwidget.h"
inline QString range(double x, double y) 
{
	return QString::number(x).append("-").append(QString::number(y));
}
QgsPlanningToolBox::QgsPlanningToolBox()
{
	this->setupUi(this);
	QgsEcologicalWizard *dlg1 = new QgsEcologicalWizard();
	
	QMap<QString,QString> data;
	data.insert(range(0.77,2.86),QString::number(1));
	data.insert(range(2.86,3.48),QString::number(2));
	data.insert(range(3.48,4.19),QString::number(3));
	data.insert(range(4.19,5.68),QString::number(4));

	QgsRasterReclassify *dlg2 = new QgsRasterReclassify(QString::fromLocal8Bit("生态适宜性综合得分"),data);

	PlanningDialog *dlg3 = new PlanningDialog();

	BuDianGuiHua *dlg4 = new BuDianGuiHua();

	ZhengZhiYinSu *dlg5 = new ZhengZhiYinSu();

	YouXuanDockWidget* dlg6 = new YouXuanDockWidget();

	this->horizontalLayout1->addWidget(dlg1);
	this->horizontalLayout2->addWidget(dlg2);
	this->horizontalLayout3->addWidget(dlg3);
	this->horizontalLayout4->addWidget(dlg4);
	this->horizontalLayout5->addWidget(dlg5);
	this->horizontalLayout6->addWidget(dlg6);


	treeWidget->setItemsExpandable(false);
	treeWidget->expandAll();

	connect(treeWidget, SIGNAL(itemPressed(QTreeWidgetItem*,int)), this, SLOT(slotItemPressed(QTreeWidgetItem*,int)));


	/*connect( mEcologicalToolBtn, SIGNAL(clicked()), this, SLOT(ecologyWizard()));
	connect( mPlanningToolBtn, SIGNAL(clicked()), this, SLOT(planningWizard()));
	connect( mDirectionToolBtn, SIGNAL(clicked()), this, SLOT(budianguihua()));
	connect( mPatternToolBtn, SIGNAL(clicked()), this, SLOT(pattern()));
	connect( mScoreToolBtn, SIGNAL(clicked()), this, SLOT(score()));*/
	/*connect( mDevFacBtn,SIGNAL(clicked()),this,SLOT(devFactors()));
	connect(mZhengZhiYinSuToolBtn,SIGNAL(clicked()),this,SLOT(zhengZhiYinSuDialog()));
	connect(mZhengZhiYinSuDBToolBtn,SIGNAL(clicked()),this,SLOT(zhengZhiYinSuDB()));*/
}
void QgsPlanningToolBox::ecologyWizard()
{
	QgsEcologicalWizard *dlg = new QgsEcologicalWizard();
	dlg->show();
	
}
void QgsPlanningToolBox::planningWizard()
{
	PlanningDialog *dlg = new PlanningDialog();
	dlg->show();
}
void QgsPlanningToolBox::pattern()
{
	QStringList agrs;
	agrs<<(QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\db\\kongxincun.db"))<<QString("-t")<<QString::fromLocal8Bit("空心村综合整治对策表");
	QProcess::startDetached(QgsApplication::pkgDataPath() + "\\sqlitebrowser.exe",agrs);
}




void QgsPlanningToolBox::score()
{
	QMap<QString,QString> data;
	data.insert(range(0.77,2.86),QString::number(1));
	data.insert(range(2.86,3.48),QString::number(2));
	data.insert(range(3.48,4.19),QString::number(3));
	data.insert(range(4.19,5.68),QString::number(4));
	QgsRasterReclassify *dlg = new QgsRasterReclassify(QString::fromLocal8Bit("生态适宜性综合得分"),data);
	dlg->show();
}

void QgsPlanningToolBox::budianguihua(){
	BuDianGuiHua *dlg = new BuDianGuiHua();
	dlg->show();
}

void QgsPlanningToolBox::devFactors(){
	QStringList agrs;
	agrs<<(QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\db\\kongxincun.db"))<<QString("-t")<<QString::fromLocal8Bit("村庄综合发展能力评价指标");
	QProcess::startDetached(QgsApplication::pkgDataPath() + "\\sqlitebrowser.exe",agrs);
}

void QgsPlanningToolBox::zhengZhiYinSuDialog(){
	ZhengZhiYinSu *dlg = new ZhengZhiYinSu();
	dlg->show();
}

void QgsPlanningToolBox::zhengZhiYinSuDB(){
	QStringList agrs;
	agrs<< QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\db\\kongxincun.db")<<QString("-t")<<QString::fromLocal8Bit("空心村整治策略因素");
	QProcess::startDetached(QgsApplication::pkgDataPath() + "\\sqlitebrowser.exe",agrs);
}

void QgsPlanningToolBox::slotItemPressed(QTreeWidgetItem* item,int index)
{
	QString name = item->text(0);
	if (name.compare(QString::fromLocal8Bit("整治区片划分")) == 0 || name.compare(QString::fromLocal8Bit("生态适宜性评价")) == 0)
	{
		stackedWidget->setCurrentIndex(0);
	}
	else if (name.compare(QString::fromLocal8Bit("生态适宜性分级")) == 0)
	{
		stackedWidget->setCurrentIndex(1);
	}
	else if (name.compare(QString::fromLocal8Bit("区片划分")) == 0)
	{
		stackedWidget->setCurrentIndex(2);
	}
	else if (name.compare(QString::fromLocal8Bit("整治方向选择")) == 0 || name.compare(QString::fromLocal8Bit("村庄布点规划")) == 0)
	{
		stackedWidget->setCurrentIndex(3);
	}
	else if (name.compare(QString::fromLocal8Bit("整治模式选择")) == 0 || name.compare(QString::fromLocal8Bit("模式选择")) == 0)
	{
		stackedWidget->setCurrentIndex(4);
	}
	else if (name.compare(QString::fromLocal8Bit("村庄模式优选")) == 0 || name.compare(QString::fromLocal8Bit("村庄模式选择")) == 0)
	{
		stackedWidget->setCurrentIndex(5);
	}
}