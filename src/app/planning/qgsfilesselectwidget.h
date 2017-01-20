#ifndef QGSFILESSELECTWIDGET_H
#define QGSFILESSELECTWIDGET_H

#include <QWidget>
#include <QMap>
#include "ui_filesselectwidget.h"

class QgsFilesSelectWidget : public QWidget,private Ui::QgsFilesSelectWidget
{
    Q_OBJECT

public:
    explicit QgsFilesSelectWidget(QStringList heads, QStringList files,QWidget *parent = 0);
    explicit QgsFilesSelectWidget(QWidget *parent = 0);
    ~QgsFilesSelectWidget();

private:
	virtual QString svePath();

public:
	 QTableWidget* getTableWidget(){return mTableWidget;}
	 QMap<QString,QString> getTableData();
	 QString getSavePath();
private slots:
	void save();


};

#endif // QGSFILESSELECTWIDGET_H
