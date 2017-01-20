#ifndef FILESELECTBASEWIDGET_H
#define FILESELECTBASEWIDGET_H

#include <QWidget>
#include <QTableWidget>
#include "ui_fileselectbasewidget.h"

class QgsFileSelectBaseWidget : public QWidget,private Ui::QgsFileSelectWidget
{
    Q_OBJECT

public:
    explicit QgsFileSelectBaseWidget( QWidget *parent = 0);
    ~QgsFileSelectBaseWidget();

private:

private slots:
	void setInputFile();

public:
   QString getFileName(){return mInputFileEdit->text();}
};

#endif // FILESELECTBASEWIDGET_H
