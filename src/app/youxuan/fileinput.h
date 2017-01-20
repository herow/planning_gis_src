#ifndef _FILE_INPUT_
#define _FILE_INPUT_

#include <QString>

QString randomFileName(QString srcName);

int fileCopy(QString src, QString des);

int execSQL(QString db,QString sql);

#endif