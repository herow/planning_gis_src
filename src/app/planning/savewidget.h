#ifndef SAVEWIDGET_H
#define SAVEWIDGET_H

#include <QWidget>

namespace Ui {
class SaveWidget;
}

class SaveWidget : public QWidget
{
    Q_OBJECT

public:
	enum Type{
		Save,
		Open
	};
public:
    explicit SaveWidget(Type type = Save,QWidget *parent=0);
    ~SaveWidget();

private:
    Ui::SaveWidget *ui;

public:
	QString getFilePath();

public slots:
	void setSavePath();
	void setOpenPath();

};

#endif // SAVEWIDGET_H
