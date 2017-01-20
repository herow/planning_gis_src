#include "qgsdirectionpage.h"
#include "qgsdevelopindexdialog.h"
#include "qgsdeveloprankdialog.h"

QgsDirectionPage::QgsDirectionPage()
{
    this->setupUi(this);
    connect(this->mDevelopFactorBtn,SIGNAL(clicked()),this,SLOT(developIndex()));
	connect(this->mPlanningBtn,SIGNAL(clicked()),this,SLOT(developRank()));
}
void QgsDirectionPage::developIndex()
{
    QgsDevelopIndexDialog* dlg = new QgsDevelopIndexDialog();
    dlg->show();
}

void QgsDirectionPage::developRank()
{
	QgsDevelopRankDialog* dlg = new QgsDevelopRankDialog();
	dlg->show();
}