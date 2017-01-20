#include "qgsplanningwizard.h"


QgsPlanningWizard::QgsPlanningWizard():
    mQgsIntroductionPage(new QgsIntroductionPage),
    mQgsPlanningnPage(new QgsPlanningPage),
    mQgsDirectionPage(new QgsDirectionPage),
    mQgsPatternPage(new QgsPatternPage)
{
    //将向导页加入向导
    setPage(QgsPlanningWizard::qgsIntroductionPage,mQgsIntroductionPage);
    setPage(QgsPlanningWizard::qgsPlanningPage,mQgsPlanningnPage);
    setPage(QgsPlanningWizard::qgsDirectionPage,mQgsDirectionPage);
    setPage(QgsPlanningWizard::qgsPatternPage,mQgsPatternPage);


    //去掉帮助按钮
    this->setWindowFlags(windowFlags()&~Qt::WindowContextHelpButtonHint);
    //设置导航样式
    setWizardStyle( QWizard::ModernStyle );
    setWindowTitle( "整治规划");

    //去掉向导页面按钮
    setOption( QWizard::NoBackButtonOnStartPage );
    setOption( QWizard::NoBackButtonOnLastPage );
    setOption( QWizard::NoCancelButton );

    //---------------------------------------------------
    //设置页面主标题的显示格式
    setTitleFormat(Qt::RichText);
    //设置子标题显示格�?
    setSubTitleFormat(Qt::RichText);

    //设置两个按钮
    setButtonText(QWizard::NextButton, "next>");
    setButtonText(QWizard::BackButton,"<back");

}

QgsPlanningWizard::~QgsPlanningWizard()
{
    delete mQgsIntroductionPage;
    delete mQgsPlanningnPage;
    delete mQgsDirectionPage;
    delete mQgsPatternPage;
}
