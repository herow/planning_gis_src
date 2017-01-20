#ifndef QGSINTRODUCTIONPAGE_H
#define QGSINTRODUCTIONPAGE_H

#include<QWizardPage>

#include "ui_introduction.h"

class QgsIntroductionPage : public QWizardPage,private  Ui::QgsIntroduction
{
public:
    QgsIntroductionPage();

};

#endif // QGSINTRODUCTIONPAGE_H
