#ifndef QGSFILESELECTPAGE_H
#define QGSFILESELECTPAGE_H

#include <QWizardPage>
#include <QMap>
#include "qgsfilesselectwidget.h"
class QgsFileSelectPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit QgsFileSelectPage();
	~QgsFileSelectPage();

private:
	QGridLayout *layout;
	QgsFilesSelectWidget *mFilesSelectWidget;
public:
	 void initializePage();
	 QMap<QString,QString> getTableData();
	 QString getSavePath(){return mFilesSelectWidget->getSavePath();}
};

#endif // QGSFACTORSETTINGPAGE_H