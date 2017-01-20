#ifndef FINALFANGANFORM_H
#define FINALFANGANFORM_H

#include <QWidget>

namespace Ui {
class FinalFanganForm;
}
class QSqlTableModel;
class QDataWidgetMapper;
class FinalFanganForm : public QWidget
{
    Q_OBJECT

public:
    explicit FinalFanganForm(QSqlTableModel *modelPro_Strategy,QWidget *parent = 0);
    ~FinalFanganForm();
private slots:
    void generate();
    void save();
private:
    Ui::FinalFanganForm *ui;
    QDataWidgetMapper *mapper;
    QSqlTableModel *model;
};



#endif // FINALFANGANFORM_H
