#ifndef QGSSETTINGWIDGET_H
#define QGSSETTINGWIDGET_H

#include <QWidget>
#include <QMap>
#include "ui_settingwidget.h"

class QgsSettingWidget : public QWidget,public Ui::QgsSettingWidget
{
    Q_OBJECT
public:
    explicit QgsSettingWidget(QString fileName,QWidget *parent = 0);
	explicit QgsSettingWidget(QStringList heads,QMap<QString,QString> data,QWidget *parent = 0);
	void setTable(QString fileName);

	QMap<QString,QString> getData();
private:
public:
	QTableWidget* getTableWidget(){return mTableWidget;};
    
signals:

public slots:
	void addRow();
	void delRow();
	void clearAll();
};

#endif // QGSSETTINGWIDGET_H
