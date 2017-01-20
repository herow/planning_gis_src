#ifndef YOUXUANFORM_H
#define YOUXUANFORM_H

#include <QWidget>

namespace Ui {
class YouxuanForm;
}

class YouxuanForm : public QWidget
{
    Q_OBJECT

public:
    explicit YouxuanForm(QWidget *parent = 0);
    ~YouxuanForm();

private:
    Ui::YouxuanForm *ui;
};

#endif // YOUXUANFORM_H
