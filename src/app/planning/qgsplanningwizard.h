#ifndef QGSPLANNINGWIZARD_H
#define QGSPLANNINGWIZARD_H
#include<QWizard>

#include"qgsintroductionpage.h"
#include"qgsplanningpage.h"
#include"qgsdirectionpage.h"
#include"qgspatternpage.h"


class QgsPlanningWizard : public QWizard
{
public:
    explicit QgsPlanningWizard();
    ~QgsPlanningWizard();
public:
    enum{
        qgsIntroductionPage,
        qgsPlanningPage,
        qgsDirectionPage,
        qgsPatternPage
    };
private:
    QgsIntroductionPage* mQgsIntroductionPage;
    QgsPlanningPage* mQgsPlanningnPage;
    QgsDirectionPage* mQgsDirectionPage;
    QgsPatternPage* mQgsPatternPage;
};

#endif // QGSPLANNINGWIZARD_H
