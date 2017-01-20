#ifndef KXCPLANNINGFRM_H
#define KXCPLANNINGFRM_H

#include <QWidget>

namespace Ui {
class KXCPlanningFrm;
}

class KXCPlanningFrm : public QWidget
{
    Q_OBJECT

public:
    explicit KXCPlanningFrm(QWidget *parent = 0);
    ~KXCPlanningFrm();

private:
    Ui::KXCPlanningFrm *ui;
};

#endif // KXCPLANNINGFRM_H
