#include "fileinput.h"

#include <QDir>
#include <QDateTime>
#include <QFile>
#include <sqlite3.h>


QString randomFileName(QString srcName)
{
	QDateTime curTime = QDateTime::currentDateTime();
	srcName.replace('.',curTime.toString("_yyyy_MM_dd_hh_mm_ss."));
	return srcName;
}

int fileCopy(QString src, QString des)
{
	des.replace("\\","/");  
	if (src == des){  
		return 1;  
	}  
	if (!QFile::exists(src)){  
		return -1;  
	}  
	QDir *createfile     = new QDir;  
	bool exist = createfile->exists(des);  
	if (exist){  
		createfile->remove(des);  
	}  

	if(!QFile::copy(src, des))  
	{  
		return -1;  
	}  
	return 0;
}

int execSQL(QString db, QString sql)
{
	sqlite3 *myDatabase;
	int myResult;
	char *errmsg = 0;  
	myResult = sqlite3_open_v2( db.toUtf8().data(), &myDatabase, SQLITE_OPEN_READWRITE, NULL );
	if ( myResult != SQLITE_OK )
	{
		myResult=0;
		return -1;
	}
	myResult = sqlite3_exec(myDatabase,"BEGIN EXCLUSIVE", NULL,NULL, &errmsg);
	if(myResult != SQLITE_OK)  
	{  
		myResult=0;
		return -1;
	}  

	myResult = sqlite3_exec(myDatabase,sql.toUtf8().data(),NULL,NULL,&errmsg);

	if(myResult == SQLITE_OK){
		myResult=sqlite3_exec(myDatabase,"COMMIT", NULL,NULL, &errmsg);  
		if(myResult != SQLITE_OK)  
		{  
			myResult=0;
			return -1;
		}
	}
	else
	{
		myResult=sqlite3_exec(myDatabase,"ROLLBACK", NULL,NULL, &errmsg);  
		if(myResult != SQLITE_OK)  
		{  
			myResult=0;
		}  
		return -1;
	}
	sqlite3_free(errmsg);
	sqlite3_close( myDatabase );
	return 0;
}