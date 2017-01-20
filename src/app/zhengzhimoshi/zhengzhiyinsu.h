#ifndef ZHENGZHIYINSU_H
#define ZHENGZHIYINSU_H

#include <QWidget>
#include <QHash>
#include <QComboBox>

namespace Ui {
class ZhengZhiYinSu;
}

class ZhengZhiYinSu : public QWidget
{
    Q_OBJECT

public:
    explicit ZhengZhiYinSu(QWidget *parent = 0);
    ~ZhengZhiYinSu();

private:
    Ui::ZhengZhiYinSu *ui;
	QHash<QString,QString> duice;

private:
	QString objName(QString fieldName);
	void comboBoxChange(QString name ,int index);
protected slots:
	void setDuice(int index);

	void clearAll();
	void next();
	void reject();
};

#endif // ZHENGZHIYINSU_H
