#ifndef QGSRANKBASEDIALOG_H
#define QGSRANKBASEDIALOG_H

#include <QWidget>
#include "ui_rankbase.h"

class QgsRankBaseDialog : public QWidget,private Ui::QgsRank
{
    Q_OBJECT
public:
    explicit QgsRankBaseDialog(QWidget *parent = 0);

signals:

public slots:
};

#endif // QGSRANKBASEDIALOG_H
