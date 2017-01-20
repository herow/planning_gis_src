#ifndef QGSSCORESETTINGPAGE_H
#define QGSSCORESETTINGPAGE_H

#include <QWizardPage>

namespace Ui {
class QgsScoreSettingPage;
}

class QgsScoreSettingPage : public QWizardPage
{
    Q_OBJECT

public:
    explicit QgsScoreSettingPage(QWidget *parent = 0);
    ~QgsScoreSettingPage();

private:
    Ui::QgsScoreSettingPage *ui;
};

#endif // QGSSCORESETTINGPAGE_H
