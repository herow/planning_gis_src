#ifndef WEIGUANXINGTAI_H
#define WEIGUANXINGTAI_H

#include <QDialog>

namespace Ui {
class weiguanxingtai;
}

class weiguanxingtai : public QDialog
{
    Q_OBJECT

public:
    explicit weiguanxingtai(QWidget *parent = 0);

    ~weiguanxingtai();
	private slots:
		void accept();
		void reject();
		void path();
private:
    Ui::weiguanxingtai *ui;
};

#endif // WEIGUANXINGTAI_H
