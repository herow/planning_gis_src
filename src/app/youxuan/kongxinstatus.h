#ifndef KONGXINSTATUS_H
#define KONGXINSTATUS_H

#include <QWidget>

namespace Ui {
class KongXinStatus;
}

class KongXinStatus : public QWidget
{
    Q_OBJECT

public:
    explicit KongXinStatus(QWidget *parent = 0);
    ~KongXinStatus();

private:
    Ui::KongXinStatus *ui;
};

#endif // KONGXINSTATUS_H
