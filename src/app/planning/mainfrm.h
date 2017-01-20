#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainFrm : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainFrm(QWidget *parent = 0);
    ~MainFrm();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
