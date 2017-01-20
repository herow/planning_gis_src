#include "budianguihua.h"
#include "qgsapplication.h"
#include "qgslogger.h"
#include "qgisapp.h"

#include <QTableWidgetItem>
#include <sqlite3.h>

BuDianGuiHua::BuDianGuiHua(QWidget *parent) :
    QDialog(parent)
{
    this->setupUi(this);
	tableWidget->resizeColumnsToContents();
	tableWidget->resizeRowsToContents();

	buttonBox->button(QDialogButtonBox::Ok)->setText(QString::fromLocal8Bit("确定"));
	//buttonBox->button(QDialogButtonBox::Cancel)->setText(QString::fromLocal8Bit("取消"));

	//设置权重可编辑
	connect(treeWidget,SIGNAL(itemDoubleClicked(QTreeWidgetItem*,int)),this,SLOT(editWeight(QTreeWidgetItem*,int)));  


	//设置s范围列可编辑
	for(int i = 0; i< tableWidget->rowCount();i++)
	{
		int j=0;
		for (;j<tableWidget->columnCount()-1;j++)
		{
			tableWidget->item(i, j)->setFlags(tableWidget->item(i,j)->flags()&(~Qt::ItemIsEditable));
		}
		tableWidget->item(i, j)->setFlags(tableWidget->item(i, j)->flags()|Qt::ItemIsEditable);
	}

	connect(buttonBox->button(QDialogButtonBox::Ok),SIGNAL(clicked()),this,SLOT(accept()));
	//connect(buttonBox->button(QDialogButtonBox::Cancel),SIGNAL(clicked()),this,SLOT(reject()));
	setCounties();
	resize(650,500);
}

BuDianGuiHua::~BuDianGuiHua()
{

}


void BuDianGuiHua::accept()
{
	QString county = comboBox->currentText();
	for (int i=0;i<6;i++)
	{
		types[i].type = tableWidget->item(i,0)->text();
		QString range = tableWidget->item(i,3)->text();
		QStringList ranges = range.split("-");
		types[i].min = ranges[0].toDouble();
		types[i].max = ranges[1].toDouble();
	}
	
	

	QHash<QString,double> hashS;

	QTreeWidgetItemIterator it(treeWidget);
	while (*it)
	{
		QTreeWidgetItem* parent=(*it)->parent();
		if (NULL ==parent)
		{

		} 
		else
		{
			double weight = (*it)->text(1).toDouble()*parent->text(1).toDouble();
			QString village = (*it)->text(0).trimmed();
			QgsDebugMsg(QString("name:%1,value:%2").arg(village,QString::number(weight)));
			
			QVector<BuDianGuiHua::name_value> temp = valueByOder(village,county);
			QgsDebugMsg(QString("name:%1,size:%2").arg(village,QString::number(temp.size())));
			for (int i=0;i<temp.size();i++)
			{
				if (hashS.contains(temp[i].name))
				{
					hashS[temp[i].name]+=weight*temp[i].value;
				}
				else
				{
					hashS[temp[i].name]=weight*temp[i].value;
				}
			}
		}
		it++;
	}

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
	
	for(QHash<QString,double>::Iterator it = hashS.begin();it!=hashS.end();it++)
	{
		QString updateSQL = QString::fromLocal8Bit("UPDATE \"村庄综合发展能力评价指标\" SET `村庄类型` = \"@type\",`S` = @S WHERE  `村名称` = \"@village\"");
		updateSQL.replace("@type",getType(it.value())).replace("@village",it.key()).replace("@S",QString::number(it.value()));
		myResult += sqlite3_exec(myDatabase,updateSQL.toUtf8().data(),NULL,NULL,&errmsg);
	}
	if(myResult == SQLITE_OK){
		myResult=sqlite3_exec(myDatabase,"COMMIT", NULL,NULL, &errmsg);  
		if(myResult != SQLITE_OK)  
		{  
			QgsDebugMsg( QString(errmsg));
			myResult=0;
			Q_ASSERT( myResult == SQLITE_OK ); 
		}  
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

	static bool isFirst = true;
	if (isFirst)
	{
		QStringList list;
		list.append(QString::fromLocal8Bit("村庄综合发展能力评价指标:any"));
		QgisApp::instance()->loadOGRSublayers(QString("SQLite"),QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\db\\kongxincun.db"),list);
		isFirst = false;
	}
	

	//QDialog::accept();
}

void BuDianGuiHua::setCounties()
{
	//Setup connection to the existing custom CRS database:
	sqlite3      *myDatabase;
	const char   *myTail;
	sqlite3_stmt *myPreparedStatement;
	int           myResult;
	//check the db is available
	myResult = sqlite3_open_v2( (QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\db\\kongxincun.db")).toUtf8().data(), &myDatabase, SQLITE_OPEN_READONLY, NULL );
	if ( myResult != SQLITE_OK )
	{
		QgsDebugMsg( QString( "Can't open database: %1" ).arg( sqlite3_errmsg( myDatabase ) ) );
		// XXX This will likely never happen since on open, sqlite creates the
		//     database if it does not exist.
		Q_ASSERT( myResult == SQLITE_OK );
	}
	QString mySql = QString::fromLocal8Bit("select distinct 乡名称 from 村庄综合发展能力评价指标");
	QgsDebugMsg( QString( "Query to populate existing list:%1" ).arg( mySql ) );
	myResult = sqlite3_prepare( myDatabase, mySql.toUtf8(), mySql.toUtf8().length(), &myPreparedStatement, &myTail );
	// XXX Need to free memory from the error msg if one is set
	if ( myResult == SQLITE_OK )
	{
		int i=0;
		while ( sqlite3_step( myPreparedStatement ) == SQLITE_ROW )
		{
			comboBox->insertItem(i,QString::fromUtf8(( char* ) sqlite3_column_text( myPreparedStatement, 0 )));
			i++;
		}
	}
	else
	{
		QgsDebugMsg( QString( "Populate list query failed: %1" ).arg( mySql ) );
	}
	sqlite3_finalize( myPreparedStatement );
	sqlite3_close( myDatabase );
}

void BuDianGuiHua::editWeight(QTreeWidgetItem* item,int column)
{
	if (column==1) 
	{
		item->setFlags(item->flags()|Qt::ItemIsEditable);
	}
	else
	{         
		item->setFlags(item->flags()&~(Qt::ItemIsEditable));
	}
}

void BuDianGuiHua::reject()
{
	QDialog::reject();
}

QVector<BuDianGuiHua::name_value> BuDianGuiHua::valueByOder(QString village,QString county)
{
	sqlite3      *myDatabase;
	const char   *myTail;
	sqlite3_stmt *myPreparedStatement;
	int           myResult;
	myResult = sqlite3_open_v2( (QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\db\\kongxincun.db")).toUtf8().data(), &myDatabase, SQLITE_OPEN_READONLY, NULL );
	if ( myResult != SQLITE_OK )
	{
		QgsDebugMsg( QString( "Can't open database: %1" ).arg( sqlite3_errmsg( myDatabase ) ) );
		
		Q_ASSERT( myResult == SQLITE_OK );
	}

	QVector<name_value> data;
	QString querySQL = QString::fromLocal8Bit("SELECT `村名称`, `@field` FROM \"村庄综合发展能力评价指标\" WHERE `乡名称` =  \"@value\"");
	querySQL.replace("@field",village);
	querySQL.replace("@value",county);
	myResult = sqlite3_prepare( myDatabase, querySQL.toUtf8(), querySQL.toUtf8().length(), &myPreparedStatement, &myTail );
	if ( myResult == SQLITE_OK )
	{
		while ( sqlite3_step( myPreparedStatement ) == SQLITE_ROW )
		{
			name_value temp;
			temp.name = QString::fromUtf8(( char* ) sqlite3_column_text( myPreparedStatement, 0 ));
			temp.value = sqlite3_column_double( myPreparedStatement, 1 );
			data.push_back(temp);
		}
	}
	else
	{
		QgsDebugMsg( QString( "Populate list query failed: %1" ).arg( querySQL ) );
	}
	sqlite3_finalize( myPreparedStatement );
	sqlite3_close( myDatabase );

	return data;
}

QString BuDianGuiHua::getType(double value){
	for (int i=0;i<6;i++)
	{
		if (value >= types[i].min && value < types[i].max)
		{
			return types[i].type;
		}
	}
	return QString("Unknown");
}