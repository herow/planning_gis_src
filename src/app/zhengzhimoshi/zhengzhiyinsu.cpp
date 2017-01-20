#include "zhengzhiyinsu.h"
#include "ui_zhengzhiyinsu.h"
#include "qgslogger.h"
#include "qgsapplication.h"

#include <sqlite3.h>

ZhengZhiYinSu::ZhengZhiYinSu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ZhengZhiYinSu)
{
    ui->setupUi(this);

	ui->tableWidget->setSpan(0, 4, 4, 1);

	sqlite3      *myDatabase;
	const char   *myTail;
	sqlite3_stmt *myPreparedStatement;
	int           myResult;
	//check the db is available
	myResult = sqlite3_open_v2( (QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\db\\kongxincun.db")).toUtf8().data(), &myDatabase, SQLITE_OPEN_READONLY, NULL );
	if ( myResult != SQLITE_OK )
	{
		Q_ASSERT( myResult == SQLITE_OK );
	}
	QString mySql = QString::fromLocal8Bit("select distinct 乡名称 from 行政区划表");
	myResult = sqlite3_prepare( myDatabase, mySql.toUtf8(), mySql.toUtf8().length(), &myPreparedStatement, &myTail );
	// XXX Need to free memory from the error msg if one is set
	if ( myResult == SQLITE_OK )
	{
		int i=0;
		while ( sqlite3_step( myPreparedStatement ) == SQLITE_ROW )
		{
			ui->comboBoxXiang->insertItem(i,QString::fromUtf8(( char* ) sqlite3_column_text( myPreparedStatement, 0 )));
			i++;
		}
	}

	mySql = QString::fromLocal8Bit("select distinct 村名称 from 行政区划表");
	myResult = sqlite3_prepare( myDatabase, mySql.toUtf8(), mySql.toUtf8().length(), &myPreparedStatement, &myTail );
	// XXX Need to free memory from the error msg if one is set
	if ( myResult == SQLITE_OK )
	{
		int i=0;
		while ( sqlite3_step( myPreparedStatement ) == SQLITE_ROW )
		{
			ui->comboBoxCun->insertItem(i,QString::fromUtf8(( char* ) sqlite3_column_text( myPreparedStatement, 0 )));
			i++;
		}
	}


	QList<QComboBox *> list= this->findChildren<QComboBox *>();
	foreach(QComboBox* obj,list){
		QString name = obj->objectName();
		if (name.compare(QString("comboBoxXiang"))==0 || name.compare(QString("comboBoxCun"))==0)
		{
			continue;
		}
		obj->insertItem(0,QString::fromLocal8Bit("请选择"));
		connect(obj, SIGNAL(currentIndexChanged(int)), this, SLOT(setDuice(int)));
	}

	int cols = ui->tableWidget->columnCount();
	int rows = ui->tableWidget->rowCount();
	for (int i=0;i<rows;i++)
	{
		for (int j=0;j<cols;j++)
		{
			ui->tableWidget->setItem(i,j,new QTableWidgetItem());
		}
	}

	//sqlite3      *myDatabase;
	//const char   *myTail;
	//sqlite3_stmt *myPreparedStatement;
	//int           myResult;
	myResult = sqlite3_open_v2( (QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\db\\kongxincun.db")).toUtf8().data(), &myDatabase, SQLITE_OPEN_READONLY, NULL );
	if ( myResult != SQLITE_OK )
	{
		QgsDebugMsg( QString( "Can't open database: %1" ).arg( sqlite3_errmsg( myDatabase ) ) );
		Q_ASSERT( myResult == SQLITE_OK );
	}
	mySql = QString::fromLocal8Bit("select 因素,分级,对策  from 整治对策表");
	QgsDebugMsg( QString( "Query to populate existing list:%1" ).arg( mySql ) );
	myResult = sqlite3_prepare( myDatabase, mySql.toUtf8(), mySql.toUtf8().length(), &myPreparedStatement, &myTail );
	if ( myResult == SQLITE_OK )
	{
		while ( sqlite3_step( myPreparedStatement ) == SQLITE_ROW )
		{
			QString name = objName(QString::fromUtf8(( char* ) sqlite3_column_text( myPreparedStatement, 0)));
			QgsDebugMsg(QString("%1,%2").arg(name,QString::fromUtf8(( char* ) sqlite3_column_text( myPreparedStatement, 1 ))));
			QComboBox* obj =  this->findChildren<QComboBox*>(name)[0];       
			obj->insertItem(obj->count(),QString::fromUtf8(( char* ) sqlite3_column_text( myPreparedStatement, 1 )));
			QString key = QString("%1_%2").arg(name,QString::number(obj->count()-1));
			QString val = QString::fromUtf8(( char* ) sqlite3_column_text( myPreparedStatement, 0)).append(QString::fromLocal8Bit("："))
									.append(QString::fromUtf8(( char* ) sqlite3_column_text( myPreparedStatement, 1))).append(QString::fromLocal8Bit("，"))
									.append(QString::fromUtf8(( char* ) sqlite3_column_text( myPreparedStatement, 2)));
			duice.insert(key,val);
		}
	}
	else
	{
		QgsDebugMsg( QString( "Populate list query failed: %1" ).arg( mySql ) );
	}
	sqlite3_finalize( myPreparedStatement );
	sqlite3_close( myDatabase );


	connect(ui->clearBtn,SIGNAL(clicked()),this,SLOT(clearAll()));
	connect(ui->nextBtn,SIGNAL(clicked()),this,SLOT(next()));
	//connect(ui->closeBtn,SIGNAL(clicked()),this,SLOT(reject()));
}

ZhengZhiYinSu::~ZhengZhiYinSu()
{
    delete ui;
}


QString ZhengZhiYinSu::objName(QString fieldName)
{
	if (QString::fromLocal8Bit("水文").compare(fieldName) == 0)
	{
		return QString("SWComBoBox_0_0");
	}
	if (QString::fromLocal8Bit("土地覆被").compare(fieldName)== 0)
	{
		return QString("TDFBComBoBox_0_1");
	}
	if (QString::fromLocal8Bit("坡度").compare(fieldName)== 0)
	{
		return QString("PDComBoBox_0_2");
	}
	if (QString::fromLocal8Bit("地质灾害").compare(fieldName)== 0)
	{
		return QString("DZZGComBoBox_0_3");
	}
	if (QString::fromLocal8Bit("村庄区位条件").compare(fieldName)== 0)
	{
		return QString("QWTJComBoBox_1_0");
	}
	if (QString::fromLocal8Bit("村庄分布密度").compare(fieldName)== 0)
	{
		return QString("CZFBMDComBoBox_1_1");
	}
	if (QString::fromLocal8Bit("基础设施").compare(fieldName)== 0)
	{
		return QString("JCSSComBoBox_2_0");
	}
	if (QString::fromLocal8Bit("公服设施").compare(fieldName)== 0)
	{
		return QString("GFSSComBoBox_2_1");
	}
	if (QString::fromLocal8Bit("非农产业比重").compare(fieldName)== 0)
	{
		return QString("FNCYBZComBoBox_2_2");
	}
	if (QString::fromLocal8Bit("常住人口比重").compare(fieldName)== 0)
	{
		return QString("CZRKBZComBoBox_3_0");
	}
	if (QString::fromLocal8Bit("废弃率").compare(fieldName)== 0)
	{
		return QString("FQLComBoBox_3_1");
	}
	if (QString::fromLocal8Bit("空置率").compare(fieldName)== 0)
	{
		return QString("KZLComBoBox_3_3");
	}
	if (QString::fromLocal8Bit("空废宗地聚集度").compare(fieldName)== 0)
	{
		return QString("KFZDJJDComBoBox_3_2");
	}
	return NULL;
}

void ZhengZhiYinSu::comboBoxChange(QString name ,int index){
	QString key = QString("%1_%2").arg(name,QString::number(index));
	QgsDebugMsg(QString("%1:%2").arg(key,duice[key]));
	QStringList list = name.split("_");
	QString result;
	if (index)
	{
		result = duice[key];
	}
	int col = list[1].toInt();
	int row = list[2].toInt();
	QTableWidgetItem* item = ui->tableWidget->item(row,col);
	if(item){
		item->setText(duice[key]);
	}
	else{
		ui->tableWidget->setItem(row,col,new QTableWidgetItem(duice[key]));
	}
}

void ZhengZhiYinSu::setDuice(int index){
	comboBoxChange(sender()->objectName(),index);
}

void ZhengZhiYinSu::clearAll(){
	/*ui->comboBoxCun->setText(QString());
	ui->comboBoxXiang->setText(QString());*/
	QList<QComboBox *> list= this->findChildren<QComboBox *>();
	foreach(QComboBox* obj,list){
		obj->setCurrentIndex(0);
	}
	for (int i = 0; i < 4; i ++)
	{
		for (int j = 0; j < 4; j ++)
		{
			ui->tableWidget->item(i,j)->setText(QString());
		}
	}
	ui->tableWidget->item(0,4)->setText(QString());
}

void ZhengZhiYinSu::reject(){
	QWidget::close();
}

void ZhengZhiYinSu::next(){
	sqlite3 *myDatabase;
	int myResult;
	char *errmsg = 0;  
	myResult = sqlite3_open_v2( (QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\db\\kongxincun.db")).toUtf8().data(), &myDatabase, SQLITE_OPEN_READWRITE, NULL );
	if ( myResult != SQLITE_OK )
	{
		QgsDebugMsg( QString( "Can't open database: %1" ).arg( sqlite3_errmsg( myDatabase ) ) );
		myResult=0;
		Q_ASSERT( myResult == SQLITE_OK );
	}
	myResult = sqlite3_exec(myDatabase,"BEGIN EXCLUSIVE", NULL,NULL, &errmsg);
	if(myResult != SQLITE_OK)  
	{  
		QgsDebugMsg( QString(errmsg));
		myResult=0;
		Q_ASSERT( myResult == SQLITE_OK ); 
	}  

	
	QString CM = ui->comboBoxCun->currentText();
	QString XM = ui->comboBoxXiang->currentText();
	QString JCTJ = ui->tableWidget->item(0,0)->text().append(QString::fromLocal8Bit("；")).append(ui->tableWidget->item(1,0)->text()).append(QString::fromLocal8Bit("；")).append(ui->tableWidget->item(2,0)->text()).append(QString::fromLocal8Bit("；")).append(ui->tableWidget->item(3,0)->text());
	QString KJXT = ui->tableWidget->item(0,1)->text().append(QString::fromLocal8Bit("；")).append(ui->tableWidget->item(1,1)->text());
	QString FZDJ = ui->tableWidget->item(0,2)->text().append(QString::fromLocal8Bit("；")).append(ui->tableWidget->item(1,2)->text()).append(QString::fromLocal8Bit("；")).append(ui->tableWidget->item(2,2)->text());
	QString KXHCD = ui->tableWidget->item(0,3)->text().append(QString::fromLocal8Bit("；")).append(ui->tableWidget->item(1,3)->text()).append(QString::fromLocal8Bit("；")).append(ui->tableWidget->item(2,3)->text()).append(QString::fromLocal8Bit("；")).append(ui->tableWidget->item(3,3)->text());
	QString ZHYJ =  ui->tableWidget->item(0,4)->text();
 	QString insertSQL = QString::fromLocal8Bit("INSERT INTO \"空心村综合整治对策表\" VALUES (\"%1\",\"%2\",\"%3\",\"%4\",\"%5\",\"%6\",\"%7\");").arg(CM,XM,JCTJ,KJXT,FZDJ,KXHCD,ZHYJ);
	myResult += sqlite3_exec(myDatabase,insertSQL.toUtf8().data(),NULL,NULL,&errmsg);
	QList<QComboBox *> list= this->findChildren<QComboBox *>();
	
	insertSQL = QString::fromLocal8Bit("INSERT INTO `空心村整治策略因素` VALUES ('CM','XM','PDComBoBox_0_2','TDFBComBoBox_0_1','SWComBoBox_0_0','CZFBMDComBoBox_1_1','QWTJComBoBox_1_0','JCSSComBoBox_2_0','GFSSComBoBox_2_1','FNCYBZComBoBox_2_2','CZRKBZComBoBox_3_0','FQLComBoBox_3_1','KFZDJJDComBoBox_3_2','KZLComBoBox_3_3');");
	foreach(QComboBox* obj,list){
		insertSQL.replace(obj->objectName(),obj->currentText());
	}
	insertSQL.replace("CM",CM);
	insertSQL.replace("XM",XM);

	myResult += sqlite3_exec(myDatabase,insertSQL.toUtf8().data(),NULL,NULL,&errmsg);

	if(myResult == SQLITE_OK){
		myResult=sqlite3_exec(myDatabase,"COMMIT", NULL,NULL, &errmsg);  
		if(myResult != SQLITE_OK)  
		{  
			QgsDebugMsg( QString(errmsg));
			myResult=0;
			Q_ASSERT( myResult == SQLITE_OK );
		}
		clearAll();
	}
	else
	{
		myResult=sqlite3_exec(myDatabase,"ROLLBACK", NULL,NULL, &errmsg);  
		if(myResult != SQLITE_OK)  
		{  
			QgsDebugMsg( QString(errmsg));
			
			myResult=0;
			Q_ASSERT( myResult == SQLITE_OK ); 
		}  		  
	}
	sqlite3_free(errmsg);
	sqlite3_close( myDatabase );
	
}