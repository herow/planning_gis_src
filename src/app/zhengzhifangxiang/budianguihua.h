#ifndef BUDIANGUIHUA_H
#define BUDIANGUIHUA_H

#include <QWidget>
#include <QDialog>
#include "qgssettingwidget.h"
#include "ui_budianguihua.h"

namespace Ui {
class BuDianGuiHua;
}

class BuDianGuiHua : public QDialog,private Ui::BuDianGuiHua
{
    Q_OBJECT

public:
    explicit BuDianGuiHua(QWidget *parent = 0);
    ~BuDianGuiHua();

private:

	QgsSettingWidget *mWeightWidget;

private:
	void setCounties();
	
private slots:
	void accept();
	void editWeight(QTreeWidgetItem*,int);
	void reject();

private:

	typedef struct  
	{
		QString name;
		double value;
	} name_value;
	typedef struct
	{
		double value;
		int frequency;
	}value_frequency;

	QVector<name_value> valueByOder(QString village,QString county);


	typedef struct{
		QString type;
		double min;
		double max;
	} Type;
	Type types[6];

	QString getType(double value);
};

#endif // BUDIANGUIHUA_H
