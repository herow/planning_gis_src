#ifndef QGSDIRECTIONPAGE_H
#define QGSDIRECTIONPAGE_H

#include<QWizardPage>

#include"ui_direction.h"
#include"qgsdevelopindexdialog.h"

class QgsDirectionPage : public QWizardPage,private Ui::QgsDirection
{
    Q_OBJECT
public:
    explicit QgsDirectionPage();
private slots:
    void developIndex();
	void developRank();
};

#endif // QGSDIRECTIONPAGE_H
