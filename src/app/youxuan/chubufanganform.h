#ifndef CHUBUFANGANFORM_H
#define CHUBUFANGANFORM_H

#include <QWidget>

namespace Ui {
class ChuBuFangAnForm;
}
class QSqlTableModel;
class QDataWidgetMapper;
class ChuBuFangAnForm : public QWidget
{
    Q_OBJECT

public:
    explicit ChuBuFangAnForm(QSqlTableModel *modelPro_Strategy,QWidget *parent = 0);
    ~ChuBuFangAnForm();

private slots:
    void generate();
    void save();

private:
    Ui::ChuBuFangAnForm *ui;    
    QDataWidgetMapper *mapper;
    QSqlTableModel *model;
protected:
    void closeEvent(QCloseEvent *event);
};

#endif // CHUBUFANGANFORM_H
