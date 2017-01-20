#ifndef MAINWIDGET_H
#define MAINWIDGET_H

#include <QWidget>
#include <QLabel>
class QgisApp;
class QSplashScreen;
class QVBoxLayout;
class TitleBar;
namespace Ui {
class mainwidget;
}

class mainwidget : public QWidget
{
    Q_OBJECT

public:
    explicit mainwidget(QSplashScreen *splash,bool restorePlugins = true,QWidget *parent = 0);
    ~mainwidget();
    QgisApp * p_qgis;
    void setQgis(QgisApp* qgis);
	void resizeEvent ( QResizeEvent * event );

	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
private:
    Ui::mainwidget *ui;
	QLabel *title;
	TitleBar *titleBar;
	QWidget *content;
	QPoint oldPos;
	bool mouseDown;
	bool left, right, bottom;
};

#endif // MAINWIDGET_H
