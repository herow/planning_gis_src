#ifndef DIAOCHAFORM_H
#define DIAOCHAFORM_H

#include <QWidget>

namespace Ui {
class DiaoChaForm;
}

class DiaoChaForm : public QWidget
{
    Q_OBJECT

public:
    explicit DiaoChaForm(QWidget *parent = 0);
    ~DiaoChaForm();

private:
    Ui::DiaoChaForm *ui;
};

#endif // DIAOCHAFORM_H
