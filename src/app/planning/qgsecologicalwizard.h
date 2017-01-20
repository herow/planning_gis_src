#ifndef QGSECOLOGICALWIZARD_H
#define QGSECOLOGICALWIZARD_H

#include <QWizard>
#include "qgsfactorsettingpage.h"
#include "qgsfilesselectpage.h"


class QgsEcologicalWizard : public QWizard
{
    Q_OBJECT

public:
    explicit QgsEcologicalWizard(QWidget *parent = 0);
    ~QgsEcologicalWizard();
public:
    enum{
       factors,
       files,
       scores
    };
private:
	QgsFactorSettingPage *mFactorsSetting;
	QgsFileSelectPage *mFilesSetting;
	QgsFactorSettingPage *mScoresSetting;

protected slots:
	void accept ();
};

#endif // QGSECOLOGICALWIZARD_H
