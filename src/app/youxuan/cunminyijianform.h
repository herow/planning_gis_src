#ifndef CUNMINYIJIANFORM_H
#define CUNMINYIJIANFORM_H

#include <QWidget>

namespace Ui {
class CunMinYIjianForm;
}

class CunMinYIjianForm : public QWidget
{
    Q_OBJECT

public:
    explicit CunMinYIjianForm(QWidget *parent = 0);
    ~CunMinYIjianForm();

private:
    Ui::CunMinYIjianForm *ui;
};

#endif // CUNMINYIJIANFORM_H
