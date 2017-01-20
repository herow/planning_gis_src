#include "qgsplanningpage.h"
#include "qgsecologicalindexdialog.h"
#include"qgsecologicalrankdialog.h"

QgsPlanningPage::QgsPlanningPage()
{
    this->setupUi(this);
    connect(this->mFactorBtn,SIGNAL(clicked()),this,SLOT(ecologicalIndex()));
	connect(this->mScoreBtn,SIGNAL(clicked()),this,SLOT(ecologicalRank()));
}


void QgsPlanningPage::ecologicalIndex()
{
    QgsEcologicalIndexDialog* dlg = new QgsEcologicalIndexDialog();
    dlg->show();
}

void QgsPlanningPage::ecologicalRank()
{

	QgsEcologicalRankDialog* dlg = new QgsEcologicalRankDialog();
	dlg->show();
}