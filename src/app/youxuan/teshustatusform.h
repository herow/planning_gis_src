#ifndef TESHUSTATUSFORM_H
#define TESHUSTATUSFORM_H

#include <QWidget>

namespace Ui {
class TeShuStatusForm;
}

class TeShuStatusForm : public QWidget
{
    Q_OBJECT

public:
    explicit TeShuStatusForm(QWidget *parent = 0);
    ~TeShuStatusForm();

private:
    Ui::TeShuStatusForm *ui;
};

#endif // TESHUSTATUSFORM_H
