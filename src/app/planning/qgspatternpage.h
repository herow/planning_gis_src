#ifndef QGSPATTERNPAGE_H
#define QGSPATTERNPAGE_H

#include<QWizardPage>

#include"ui_pattern.h"

class QgsPatternPage : public QWizardPage,private Ui::QgsPattern
{
public:
    QgsPatternPage();
};

#endif // QGSPATTERNPAGE_H
