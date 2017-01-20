#include "youxuandockwidget.h"
#include "ui_youxuandockwidget.h"
#include "kongxinstatus.h"
#include "diaochaform.h"
#include "imagecollection.h"
#include "fangtang.h"
#include "teshustatusform.h"
#include "wenti_celueform.h"
#include "chubufanganform.h"
#include "cunminyijianform.h"
#include "zhengfuyaoqiuform.h"
#include "finalfanganform.h"
#include "connection.h"

#include "comboboxdelegate.h"
#include "horizontal_proxy_model.h"
#include "view.h"
#include <QSqlDatabase>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QtSql>
#include <QtGui>
#include <QGridLayout>
#include "qgsapplication.h"

#include <sqlite3.h>

YouXuanDockWidget::YouXuanDockWidget(QWidget *parent) :
    QDockWidget(parent),
    ui(new Ui::YouXuanDockWidget)
{   
    ui->setupUi(this);
	 this->setWindowFlags(Qt::FramelessWindowHint);
	//const QString p=QgsApplication::pluginPath();

	//Setup connection to the existing custom CRS database:
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
			ui->comboBoxXiangname->insertItem(i,QString::fromUtf8(( char* ) sqlite3_column_text( myPreparedStatement, 0 )));
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
			ui->comboBoxCunname->insertItem(i,QString::fromUtf8(( char* ) sqlite3_column_text( myPreparedStatement, 0 )));
			i++;
		}
	}

	sqlite3_finalize( myPreparedStatement );
	sqlite3_close( myDatabase );

	createConnection(QString::fromLocal8Bit("\\data\\db\\test.db"));

    connect( ui->btnKongxinStatus, SIGNAL(clicked()), this, SLOT( show_kongxin_status() ) );

    connect( ui->btnSurveyForm, SIGNAL(clicked()), this, SLOT( show_surveyForm() ) );
    connect( ui->btnPictureCollet, SIGNAL(clicked()), this, SLOT( show_picturecollect() ) );
    connect( ui->btnSemiStructSurvey, SIGNAL(clicked()), this, SLOT( show_semisurvey() ) );

    connect( ui->btnSpecStatus, SIGNAL(clicked()), this, SLOT( show_specstatus() ) );

    connect( ui->btnProblemStrategy, SIGNAL(clicked()), this, SLOT( show_ProblemStrategy() ) );

    connect( ui->btnInitStrategy, SIGNAL(clicked()), this, SLOT( show_InitStrategy() ) );
    connect( ui->btnPublicOpinion, SIGNAL(clicked()), this, SLOT( show_PublicOpinion() ) );
    connect( ui->btnGovOpinion, SIGNAL(clicked()), this, SLOT( show_GovOpinion() ) );
    connect( ui->btnFinalSolution, SIGNAL(clicked()), this, SLOT( show_FinalSolution() ) );
    connect( ui->comboBoxXiangname, SIGNAL(currentIndexChanged(int)),this,SLOT(setSelection(int)));
    connect( ui->comboBoxCunname, SIGNAL(currentIndexChanged(int)),this,SLOT(setSelection(int)));

//    if (!createConnection())
//        return  ;
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
	QTextCodec *codec =QTextCodec::codecForName("gbk");

    const char * strtable2 = "核心问题与整治策略";

    QString tableName2=QString::fromLocal8Bit(strtable2);
    model_youxuan= new QSqlTableModel;
    model_youxuan->setTable(tableName2);
 //   model_youxuan->setEditStrategy(QSqlTableModel::OnManualSubmit);


    mapper = new QDataWidgetMapper(this);
    mapper->setModel(model_youxuan);
    mapper->setItemDelegate(new ComboBoxDelegate(this));
    mapper->addMapping(ui->comboxKongxc,6);
    mapper->addMapping(ui->comboxZhengzhi, 7);
    mapper->addMapping(ui->lineEditZonghushu, 8);
    mapper->addMapping(ui->lineEditTongyi, 9);
    mapper->addMapping(ui->lineEditFandui, 10);
    mapper->addMapping(ui->comboxGaizaoyiyuan, 11);

    setSelection(0);

	if(QSqlDatabase::contains(QString("kongxincun"))){

		m_db = QSqlDatabase::database(QString("kongxincun"));
	}
	else{  
		m_db = QSqlDatabase::addDatabase("QSQLITE",QString("kongxincun"));
	}

	if(!m_db.isOpen())
	{
		m_db.setDatabaseName(QgsApplication::pkgDataPath() +  QString::fromLocal8Bit("\\data\\db\\kongxincun.db"));
		if(!m_db.open())
		{
			QMessageBox::critical(0,QObject::tr("Database Error"),m_db.lastError().text());

		}

	}
    modelPro_Strategy= new QSqlTableModel;
    model_InitialStrategy =new QSqlTableModel;
    model_FinalStrategy =new QSqlTableModel;
   // chubufangan= new ChuBuFangAnForm(modelPro_Strategy);
    model_SurveyForm = new QSqlQueryModel;
    model_SemiSurvey = new QSqlQueryModel;
    model_SpecStatus = new QSqlQueryModel;
    model_strategy= new QSqlTableModel(0,m_db);
    model_PublicOpinion=new QSqlQueryModel;
    model_GovOpinion=new QSqlQueryModel;

	if (m_db.isOpen())
	{
		m_db.close();
	}

	
   // wid_wenti_celue = new WenTi_CeLueForm(model_strategy,modelPro_Strategy);
}
void YouXuanDockWidget::deConnect(QObject* ptr)
{
	if (m_db.isOpen())
	{
		m_db.close();
	}

}
void YouXuanDockWidget::setSelection(int idx)
{
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
    QTextCodec *codec =QTextCodec::codecForName("gbk");
    const char * strCunname = "村名称";
    const char * strXiangname = "乡名称";
    QString cunName=QString::fromLocal8Bit(strCunname);
    QString xiangName=QString::fromLocal8Bit(strXiangname);

    QString fullSql = QString( " `%1`='%2' and `%3`='%4'" )
            .arg(cunName).arg(ui->comboBoxCunname->currentText())
            .arg(xiangName).arg(ui->comboBoxXiangname->currentText());


    model_youxuan->setFilter(fullSql);
    model_youxuan->select();


	if (model_youxuan->rowCount() == 0)
	{
		QSqlRecord record = model_youxuan->record();

		record.setValue(cunName,ui->comboBoxCunname->currentText());
		record.setValue(xiangName,ui->comboBoxXiangname->currentText());
		model_youxuan->insertRecord(0,record);
		model_youxuan->submitAll(); 
	}
 //   mapper->setModel(model_youxuan);
  //  mapper->setItemDelegate(new ComboBoxDelegate(this));
//    mapper->addMapping(ui->comboxKongxc,6);
//    mapper->addMapping(ui->comboxZhengzhi, 7);
//    mapper->addMapping(ui->lineEditZonghushu, 8);
//    mapper->addMapping(ui->lineEditTongyi, 9);
//    mapper->addMapping(ui->lineEditFandui, 10);
//    mapper->addMapping(ui->comboxGaizaoyiyuan, 11);

    mapper->toFirst();
}
YouXuanDockWidget::~YouXuanDockWidget()
{
    delete ui;
	db.close();
	m_db.close();
    /*delete model_youxuan;
    delete model_SurveyForm;
    delete model_SemiSurvey;
    delete model_SpecStatus;
    delete modelPro_Strategy;
    delete model_strategy;
    delete model_PublicOpinion;
    delete model_GovOpinion;
    delete model_FinalStrategy;
    delete chubufangan;
    delete wid_SemiSurvey;
    delete wid_SpecStatus;
    delete wid_wenti_celue;
    delete chubufangan;
    delete wid_PublicOpinion;
    delete wid_GovOpinion;
    delete wid_finalStrategy;
    delete wid_picview;*/
}

void YouXuanDockWidget::show_kongxin_status()
{
	if(QSqlDatabase::contains(QString("kongxincun"))){

		m_db = QSqlDatabase::database(QString("kongxincun"));
	}
	else{  
		m_db = QSqlDatabase::addDatabase("QSQLITE",QString("kongxincun"));
	}
	
	if(!m_db.isOpen())
	{
		m_db.setDatabaseName(QgsApplication::pkgDataPath() +  QString::fromLocal8Bit("\\data\\db\\kongxincun.db"));
		if(!m_db.open())
		{
			QMessageBox::critical(0,QObject::tr("Database Error"),m_db.lastError().text());
			
		}

	}
    QSqlQueryModel *model= new QSqlTableModel;
    // Set character encoding to UTF8

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
    QTextCodec *codec =QTextCodec::codecForName("gbk");
    const char * str = "村庄综合发展能力评价指标";
    const char * strCunname = "村名称";
    const char * strXiangname = "乡名称";
    QString tableName=QString::fromLocal8Bit(str);
    QString cunName=QString::fromLocal8Bit(strCunname);
    QString xiangName=QString::fromLocal8Bit(strXiangname);

     QString fullSql;
     fullSql = QString( "select * from '%1' where `%2`='%3' and `%4`='%5'" )
             .arg( tableName ).arg(cunName).arg(ui->comboBoxCunname->currentText())
             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());
   // QMessageBox::information(NULL, "Title", fullSql, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

     model->setQuery(fullSql,m_db) ;//where id=101

    Horizontal_proxy_model* proxy_model = new Horizontal_proxy_model();
    proxy_model->setSourceModel(model);

 //   QTableView *view = new QTableView;
	//view->setModel(model);
	
	QTableView *view_kongxin_status =new QTableView;
	
    view_kongxin_status->setModel(proxy_model);
    view_kongxin_status->horizontalHeader()->hide();
	view_kongxin_status->setGeometry(QRect(500,100,400,500));
	view_kongxin_status->setWindowTitle(QString::fromLocal8Bit("村庄综合发展能力"));
    view_kongxin_status->show();
	
	if (m_db.isOpen())
	{
		m_db.close();
	}

}
void YouXuanDockWidget::show_surveyForm()
{

    // Set character encoding to UTF8

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
    QTextCodec *codec =QTextCodec::codecForName("gbk");
    const char * str = "调查问卷";
    const char * strCunname = "村名称";
    const char * strXiangname = "乡名称";
    QString tableName=QString::fromLocal8Bit(str);
    QString cunName=QString::fromLocal8Bit(strCunname);
    QString xiangName=QString::fromLocal8Bit(strXiangname);

    QString fullSql;
    fullSql = QString( "select * from '%1' where `%2`='%3' and `%4`='%5'" )
             .arg( tableName ).arg(cunName).arg(ui->comboBoxCunname->currentText())
             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());
   // QMessageBox::information(NULL, "Title", fullSql, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    model_SurveyForm->setQuery(fullSql) ;//where id=101



    QTableView *view = new QTableView;
    view->setModel(model_SurveyForm);
    view->setGeometry(QRect(100,100,900,500));
    view->show();
}
void YouXuanDockWidget::show_picturecollect()
{
//     ImageCollection * wid = new ImageCollection();
//     wid->show();

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
	QTextCodec *codec =QTextCodec::codecForName("gbk");
     const char * str = "数据图件";
     QString winName=QString::fromLocal8Bit(str);

     wid_picview=new View(winName,ui->comboBoxXiangname->currentText(),
                         ui->comboBoxCunname->currentText());
     wid_picview->setWindowTitle(winName);
     wid_picview->show();
}
void YouXuanDockWidget::show_semisurvey()
{

    //QSqlQueryModel *model= new QSqlTableModel;
    // Set character encoding to UTF8

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
	QTextCodec *codec =QTextCodec::codecForName("gbk");
    const char * str = "半结构化访谈";
    //const char * strcaption = "标题";
    const char * strCunname = "村名称";
    const char * strXiangname = "乡名称";
    QString tableName=QString::fromLocal8Bit(str);
  //  QString  caption =codec->toUnicode(strcaption);
    QString cunName=QString::fromLocal8Bit(strCunname);
    QString xiangName=QString::fromLocal8Bit(strXiangname);

    QString fullSql;
    fullSql = QString( "select * from '%1' where `%2`='%3' and `%4`='%5'" )
             .arg( tableName ).arg(cunName).arg(ui->comboBoxCunname->currentText())
             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());
//    fullSql = QString( "select `%1` from '%2' where `%3`='%4' and `%5`='%6'" )
//             .arg(caption).arg( tableName ).arg(cunName).arg(ui->comboBoxCunname->currentText())
//             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());
   // QMessageBox::information(NULL, "Title", fullSql, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    model_SemiSurvey->setQuery(fullSql) ;//where id=101


    wid_SemiSurvey = new fangtang(model_SemiSurvey);
    wid_SemiSurvey->setWindowTitle(tableName);
    wid_SemiSurvey->show();


}
void YouXuanDockWidget::show_specstatus()
{

        //QSqlQueryModel *model= new QSqlTableModel;
        // Set character encoding to UTF8

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
	QTextCodec *codec =QTextCodec::codecForName("gbk");
        const char * str = "当地特殊情况";
        const char * strcaption = "标题";
        const char * strCunname = "村名称";
        const char * strXiangname = "乡名称";

        QString tableName=QString::fromLocal8Bit(str);
        QString  caption =QString::fromLocal8Bit(strcaption);
        QString cunName=QString::fromLocal8Bit(strCunname);
        QString xiangName=QString::fromLocal8Bit(strXiangname);

        QString fullSql;
        fullSql = QString( "select * from '%1' where `%2`='%3' and `%4`='%5'" )
                 .arg( tableName ).arg(cunName).arg(ui->comboBoxCunname->currentText())
                 .arg(xiangName).arg(ui->comboBoxXiangname->currentText());
    //    fullSql = QString( "select `%1` from '%2' where `%3`='%4' and `%5`='%6'" )
    //             .arg(caption).arg( tableName ).arg(cunName).arg(ui->comboBoxCunname->currentText())
    //             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());
       // QMessageBox::information(NULL, "Title", fullSql, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

        model_SpecStatus->setQuery(fullSql) ;//where id=101
        wid_SpecStatus = new fangtang(model_SpecStatus);
        wid_SpecStatus->setWindowTitle(tableName);
        wid_SpecStatus->show();
}
void YouXuanDockWidget::show_ProblemStrategy()
{
	if(QSqlDatabase::contains(QString("kongxincun"))){

		m_db = QSqlDatabase::database(QString("kongxincun"));
	}
	else{  
		m_db = QSqlDatabase::addDatabase("QSQLITE",QString("kongxincun"));
	}

	if(!m_db.isOpen())
	{
		m_db.setDatabaseName(QgsApplication::pkgDataPath() +  QString::fromLocal8Bit("\\data\\db\\kongxincun.db"));
		if(!m_db.open())
		{
			QMessageBox::critical(0,QObject::tr("Database Error"),m_db.lastError().text());

		}

	}
	QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
	QTextCodec *codec =QTextCodec::codecForName("gbk");
    const char * strtable1 = "空心村综合整治对策表";
    //const char * strtable2 = "核心问题与整治策略";
    const char * strCunname = "村名";
    const char * strXiangname = "乡名称";
    QString tableName1=QString::fromLocal8Bit(strtable1);
    //QString tableName2=QString::fromLocal8Bit(strtable2);
    QString cunName=QString::fromLocal8Bit(strCunname);
    QString xiangName=QString::fromLocal8Bit(strXiangname);

     QString fullSql;
     //fullSql = QString( "select * from '%1' where `%2`='%3' and `%4`='%5'" )
     //        .arg( tableName1 ).arg(cunName).arg(ui->comboBoxCunname->currentText())
     //        .arg(xiangName).arg(ui->comboBoxXiangname->currentText());




     // QMessageBox::information(NULL, "Title", fullSql, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    // model_strategy->setQuery(fullSql,m_db) ;
     fullSql = QString( " `%2`='%3' and `%4`='%5'" )
             .arg(cunName).arg(ui->comboBoxCunname->currentText())
             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());
	 model_strategy->setTable(tableName1);
	 model_strategy->setFilter(fullSql);
	 model_strategy->select();
//     modelPro_Strategy->setTable(tableName2);
//     modelPro_Strategy->setFilter(fullSql);
//     modelPro_Strategy->select();



    wid_wenti_celue = new WenTi_CeLueForm(model_strategy,model_youxuan);
     wid_wenti_celue->show();

	 if (m_db.isOpen())
	 {
		 m_db.close();
	 }


}
void YouXuanDockWidget::show_InitStrategy()
{

    // Set character encoding to UTF8

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
	QTextCodec *codec =QTextCodec::codecForName("gbk");
   // const char * strtable1 = "空心化程度";
    const char * strtable2 = "核心问题与整治策略";
    const char * strCunname = "村名称";
    const char * strXiangname = "乡名称";
  //  QString tableName1=codec->toUnicode(strtable1);
    QString tableName2=QString::fromLocal8Bit(strtable2);
    QString cunName=QString::fromLocal8Bit(strCunname);
    QString xiangName=QString::fromLocal8Bit(strXiangname);

//     QString fullSql;

//     fullSql = QString( " `%2`='%3' and `%4`='%5'" )
//             .arg(cunName).arg(ui->comboBoxCunname->currentText())
//             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());

//     model_InitialStrategy->setTable(tableName2);
//     model_InitialStrategy->setFilter(fullSql);
//     model_InitialStrategy->select();

     chubufangan= new ChuBuFangAnForm(model_youxuan);


     chubufangan->show();


}
void YouXuanDockWidget::show_PublicOpinion()
{
//    CunMinYIjianForm * wid = new CunMinYIjianForm();
//    wid->show();

    // Set character encoding to UTF8

	QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
	QTextCodec *codec =QTextCodec::codecForName("gbk");
    const char * str = "村民意见";
    const char * strcaption = "标题";
    const char * strCunname = "村名称";
    const char * strXiangname = "乡名称";

    QString tableName=QString::fromLocal8Bit(str);
    QString  caption =QString::fromLocal8Bit(strcaption);
    QString cunName=QString::fromLocal8Bit(strCunname);
    QString xiangName=QString::fromLocal8Bit(strXiangname);

    QString fullSql;
    fullSql = QString( "select * from '%1' where `%2`='%3' and `%4`='%5'" )
             .arg( tableName ).arg(cunName).arg(ui->comboBoxCunname->currentText())
             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());

    model_PublicOpinion->setQuery(fullSql) ;//where id=101


    wid_PublicOpinion = new fangtang(model_PublicOpinion);
    wid_PublicOpinion->setWindowTitle(tableName);
    wid_PublicOpinion->show();
//    QTableView *view = new QTableView;
//    view->setModel(model);
//    //view->horizontalHeader()->hide();
//    view->show();

}
void YouXuanDockWidget::show_GovOpinion()
{
//    ZhengFuYaoqiuForm * wid = new ZhengFuYaoqiuForm();
//    wid->show();
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
    QTextCodec *codec =QTextCodec::codecForName("gbk");
    const char * str = "政府意见";
    const char * strcaption = "标题";
    const char * strCunname = "村名称";
    const char * strXiangname = "乡名称";

    QString tableName=QString::fromLocal8Bit(str);
    QString  caption =QString::fromLocal8Bit(strcaption);
    QString cunName=QString::fromLocal8Bit(strCunname);
    QString xiangName=QString::fromLocal8Bit(strXiangname);

    QString fullSql;
    fullSql = QString( "select * from '%1' where `%2`='%3' and `%4`='%5'" )
             .arg( tableName ).arg(cunName).arg(ui->comboBoxCunname->currentText())
             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());

    model_GovOpinion->setQuery(fullSql) ;//where id=101


    wid_GovOpinion = new fangtang(model_GovOpinion);
    wid_GovOpinion->setWindowTitle(tableName);
    wid_GovOpinion->show();
}
void YouXuanDockWidget::show_FinalSolution()
{

//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//     QTextCodec *codec =QTextCodec::codecForName("UTF-8");
//   // const char * strtable1 = "空心化程度";
//    const char * strtable2 = "核心问题与整治策略";
//    const char * strCunname = "村名称";
//    const char * strXiangname = "乡名称";
//  //  QString tableName1=codec->toUnicode(strtable1);
//    QString tableName2=codec->toUnicode(strtable2);
//    QString cunName=codec->toUnicode(strCunname);
//    QString xiangName=codec->toUnicode(strXiangname);

//     QString fullSql;

//     fullSql = QString( " `%2`='%3' and `%4`='%5'" )
//             .arg(cunName).arg(ui->comboBoxCunname->currentText())
//             .arg(xiangName).arg(ui->comboBoxXiangname->currentText());

//     model_FinalStrategy->setTable(tableName2);
//     model_FinalStrategy->setFilter(fullSql);
//     model_FinalStrategy->select();

     wid_finalStrategy= new FinalFanganForm(model_youxuan);
     wid_finalStrategy->show();
}
//bool YouXuanDockWidget::createConnetion()
//{
//    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
//    db.setDatabaseName("demo.db");
//    if (!db.open()) {
//        QMessageBox::critical(0, qApp->tr("Cannot open database"),
//            qApp->tr("Unable to establish a database connection.\n"
//                     "This example needs SQLite support. Please read "
//                     "the Qt SQL driver documentation for information how "
//                     "to build it.\n\n"
//                     "Click Cancel to exit."), QMessageBox::Cancel);
//
//    }
//	return true;
//}
void YouXuanDockWidget::closeEvent(QCloseEvent *event)
{
//    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
//    QTextCodec *codec =QTextCodec::codecForName("UTF-8");
//    const char * strcaption = "提示";
//    const char * strcontent = "是否对数据进行保存？" ;
//    const char * strok= "是";
//    const char * strno= "否";
//    const char * strcancel = "取消";
//    QString strCap=codec->toUnicode(strcaption);
//    QString strCont=codec->toUnicode(strcontent);
//    QString strOkbtn=codec->toUnicode(strok);
//    QString strNobtn=codec->toUnicode(strno);
//    QString strCancelbtn=codec->toUnicode(strcancel);

//    int r=QMessageBox::question(this,strCap,strCont,
//   strOkbtn,strNobtn);

//    QMessageBox box(QMessageBox::warning,"strCap","strCont");
//    box.setStandardButtons (QMessageBox::Ok|QMessageBox::Cancel);
//    box.setButtonText (QMessageBox::Ok,strOkbtn);
//    box.setButtonText (QMessageBox::Cancel,strCancelbtn);


//    if (r==0)
//    {
        mapper->submit();
        event->accept();
//    }
//    else
//    {
//        event->accept();
//    }
}
