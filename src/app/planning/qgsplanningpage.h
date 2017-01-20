#ifndef QGSPLANNINGPAGE_H
#define QGSPLANNINGPAGE_H

#include<QWizardPage>

#include"ui_planning.h"

class QgsPlanningPage : public QWizardPage,private Ui::QgsPlanning
{
    Q_OBJECT
public:
    QgsPlanningPage();
private slots:
    void ecologicalIndex();
	void ecologicalRank();
};

#endif // QGSPLANNINGPAGE_H
