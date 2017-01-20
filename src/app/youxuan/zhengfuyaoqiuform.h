#ifndef ZHENGFUYAOQIUFORM_H
#define ZHENGFUYAOQIUFORM_H

#include <QWidget>

namespace Ui {
class ZhengFuYaoqiuForm;
}

class ZhengFuYaoqiuForm : public QWidget
{
    Q_OBJECT

public:
    explicit ZhengFuYaoqiuForm(QWidget *parent = 0);
    ~ZhengFuYaoqiuForm();

private:
    Ui::ZhengFuYaoqiuForm *ui;
};

#endif // ZHENGFUYAOQIUFORM_H
