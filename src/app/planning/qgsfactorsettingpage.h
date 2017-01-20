#ifndef QGSFACTORSETTINGPAGE_H
#define QGSFACTORSETTINGPAGE_H

#include <QWizardPage>
#include <QMap>
#include "qgssettingwidget.h"
class QgsFactorSettingPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit QgsFactorSettingPage(QWidget *parent = 0);
	~QgsFactorSettingPage();

private:
	QGridLayout *layout;
	QgsSettingWidget *mSettingWidget;

public:
	QMap<QString,QString> getTableDate();
	QStringList getFactors();
};

#endif // QGSFACTORSETTINGPAGE_H