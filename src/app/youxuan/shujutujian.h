#ifndef SHUJUTUJIAN_H
#define SHUJUTUJIAN_H

#include <QDialog>

namespace Ui {
class shujutujian;
}

class shujutujian : public QDialog
{
    Q_OBJECT

public:
    explicit shujutujian(QWidget *parent = 0);
    ~shujutujian();

private:
    Ui::shujutujian *ui;

	private slots:
		void accept();
		void reject();
		void path();
};

#endif // SHUJUTUJIAN_H
