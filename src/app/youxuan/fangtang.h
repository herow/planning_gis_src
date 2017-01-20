#ifndef FANGTANG_H
#define FANGTANG_H

#include <QWidget>

namespace Ui {
class fangtang;
}
class QSqlQueryModel;
//class QModelIndex;
#include <QModelIndex>
class fangtang : public QWidget
{
    Q_OBJECT

public:
    fangtang(QSqlQueryModel *model,QWidget *parent = 0);
    ~fangtang();
private slots:
    void showDetail(QModelIndex index);

private:
    Ui::fangtang *ui;
    QSqlQueryModel *m_model;
};

#endif // FANGTANG_H
