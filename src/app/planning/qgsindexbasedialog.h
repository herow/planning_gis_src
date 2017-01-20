#ifndef QGSINDEXBASEDIALOG_H
#define QGSINDEXBASEDIALOG_H

#include <QWidget>
#include "ui_indexbase.h"

class QgsIndexBaseDialog : public QWidget,private Ui::QgsIndexBase
{
    Q_OBJECT
public:
    explicit QgsIndexBaseDialog(QWidget *parent = 0);

signals:

public slots:
};

#endif // QGSINDEXBASEDIALOG_H
