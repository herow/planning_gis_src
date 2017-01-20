#ifndef QGSRASTERRECLASSIFY_H
#define QGSRASTERRECLASSIFY_H

#include <QDialog>
#include <QMap>
#include "qgssettingwidget.h"
#include "savewidget.h"

class QgsRasterReclassify : public QDialog
{
    Q_OBJECT
public:
    explicit QgsRasterReclassify(QString title,QMap<QString,QString> data);
	~QgsRasterReclassify();

private:
	QgsSettingWidget* mQgsSettingWidget;
	SaveWidget* mSaveWidget;
	SaveWidget* mOpenWidget;
signals:

public slots:
	void accept();
	void reject();

};

#endif // QGSRASTERRECLASSIFY_H
