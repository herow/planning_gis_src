#ifndef WENTI_CELUEFORM_H
#define WENTI_CELUEFORM_H

#include <QWidget>

namespace Ui {
class WenTi_CeLueForm;
}
class QSqlQueryModel;
class QDataWidgetMapper;
class QSqlTableModel;
class QCloseEvent;
class WenTi_CeLueForm : public QWidget
{
    Q_OBJECT

public:
    WenTi_CeLueForm(QSqlTableModel *model,QSqlTableModel *modelPro_Strategy,QWidget *parent = 0);
    ~WenTi_CeLueForm();

private:
    Ui::WenTi_CeLueForm *ui;
    QDataWidgetMapper *mapper;
private slots:
    void save();
protected:
    void closeEvent(QCloseEvent *event);

};

#endif // WENTI_CELUEFORM_H
