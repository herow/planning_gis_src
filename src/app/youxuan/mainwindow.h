#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}
class YouXuanDockWidget;
class MainWindow2;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    YouXuanDockWidget * wizard;
    MainWindow2 *MicroDesign;
private slots:
    void showWizard();
    void showMicroDesign();
};

#endif // MAINWINDOW_H
