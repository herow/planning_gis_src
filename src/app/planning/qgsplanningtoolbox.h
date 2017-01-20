#ifndef QGSPLANNINGTOOLBOX_H
#define QGSPLANNINGTOOLBOX_H

#include <QDockWidget>
#include "ui_planningtoolbox.h"

class QgsPlanningToolBox : public QDockWidget,private Ui::QgsPlanningDockWindow
{
    Q_OBJECT
public:
    explicit QgsPlanningToolBox();

signals:

public slots:
	void planningWizard();
	void ecologyWizard();
	void devFactors();
	void pattern();
	void score();
	void budianguihua();
	void zhengZhiYinSuDialog();
	void zhengZhiYinSuDB();
	void slotItemPressed(QTreeWidgetItem*,int);
};

#endif // QGSPLANNINGTOOLBOX_H