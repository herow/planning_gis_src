#ifndef PLANNINGDIALOG_H
#define PLANNINGDIALOG_H

#include <QDialog>
#include "qgssettingwidget.h"
#include "qgsvectorlayer.h"

namespace Ui {
class PlanningDialog;
}

class PlanningDialog : public QDialog
{
    Q_OBJECT

public:
    explicit PlanningDialog(QWidget *parent = 0);
    ~PlanningDialog();

private:
    Ui::PlanningDialog *ui;
	QgsSettingWidget* mSettingWidget;

private:
	void eval(QgsVectorLayer* vl);
	QString eval(double score);
public slots:
	void openRaster();
	void openVector();
	void saveVector();
	void accept();
};

#endif // PLANNINGDIALOG_H
