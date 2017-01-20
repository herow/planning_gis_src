#include "qgsscoresettingpage.h"
#include "ui_qgsscoresettingpage.h"

QgsScoreSettingPage::QgsScoreSettingPage(QWidget *parent) :
    QWizardPage(parent),
    ui(new Ui::QgsScoreSettingPage)
{
    ui->setupUi(this);
}

QgsScoreSettingPage::~QgsScoreSettingPage()
{
    delete ui;
}
