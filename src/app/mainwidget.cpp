#include "mainwidget.h"
#include "ui_mainwidget.h"
#include "titlebar2.h"
#include <QLayout>
#include "qgisapp.h"
#include "qsplashscreen.h"
#include "qgscustomization.h"
mainwidget::mainwidget(QSplashScreen *splash,bool restorePlugins, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::mainwidget)
{
    ui->setupUi(this);
    p_qgis= new QgisApp(splash,restorePlugins,this);
    //p_qgis->completeInitialization();
    //p_qgis->show();
 //   title = new QLabel(QWidget::tr("Title bar"),this);
	//title->setStyleSheet("QLabel{border-image: url(:/log/logo.png);}");
	//title->setText(QString::fromLocal8Bit(" 空心村信息综合平台"));
	//QPalette pa;
	//pa.setColor(QPalette::WindowText,Qt::red);
	//title->setPalette(pa);
	////title->adjustSize();
 //   //title->setPixmap(QPixmap(":/log/logo.png"));
 //   title->setScaledContents(true);

	mouseDown = false;
	//setFrameShape(Panel);

	// 设置无边框窗口
	// 这会导致该窗口无法改变大小或移动
	setWindowFlags(Qt::FramelessWindowHint);
	setMouseTracking(true);
	titleBar = new TitleBar(this);
	QVBoxLayout *pLayout = new QVBoxLayout();

	pLayout->addWidget(titleBar);
	pLayout->addWidget(p_qgis);
	pLayout->setStretchFactor(titleBar,1);
	pLayout->setStretchFactor(p_qgis,5);
	pLayout->setSpacing(0);
	pLayout->setContentsMargins(0, 0, 0, 0);
	setLayout(pLayout);
	setWindowTitle(QgsCustomization::instance()->getWindowTitle());
	setWindowState(Qt::WindowMaximized);

	int flag = QgsCustomization::instance()->getType();
	if(flag == 1)
	{
		titleBar->updateTitle(QString::fromLocal8Bit("空心村综合整治信息平台"), QString(":/images/xxpt.png"));
	}
	else
	{
		titleBar->updateTitle(QString::fromLocal8Bit("空心村整治模式优选"), QString(":/images/msyx.png"));
	}
}

mainwidget::~mainwidget()
{
    delete ui;
   // delete p_qgis;
}
void mainwidget::setQgis(QgisApp* qgis)
{

    //qgis->completeInitialization();
    //qgis->hide();
    QVBoxLayout *pLayout = new QVBoxLayout();
  /*  QLabel *title = new QLabel(QWidget::tr("Title bar"));
    title->setPixmap(QPixmap(":/images/sponsors/sponsors/geosynergy.png"));
    title->setScaledContents(true);*/


    pLayout->addWidget(title);
    pLayout->addWidget(qgis);

    pLayout->setStretchFactor(title,1);
    pLayout->setStretchFactor(qgis,5);
    pLayout->setSpacing(0);
    pLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(pLayout);
}

void mainwidget::resizeEvent ( QResizeEvent * event ) 
{
	/*title->setText(QgsCustomization::instance()->getWindowTitle());
	int height = title->rect().height();
	int width = title->rect().width();
	int size = height > width  ? width /4 : height /4;
	QFont ft;
	ft.setPointSize(size);
	title->setFont(ft);*/
}

void mainwidget::mousePressEvent(QMouseEvent *e)
{
	oldPos = e->pos();
	mouseDown = e->button() == Qt::LeftButton;
}

void mainwidget::mouseMoveEvent(QMouseEvent *e)
{
	int x = e->x();
	int y = e->y();

	if (mouseDown) {
		int dx = x - oldPos.x();
		int dy = y - oldPos.y();

		QRect g = geometry();

		if (left)
			g.setLeft(g.left() + dx);
		if (right)
			g.setRight(g.right() + dx);
		if (bottom)
			g.setBottom(g.bottom() + dy);

		setGeometry(g);

		oldPos = QPoint(!left ? e->x() : oldPos.x(), e->y());
	} else {
		QRect r = rect();
		left = qAbs(x - r.left()) <= 5;
		right = qAbs(x - r.right()) <= 5;
		bottom = qAbs(y - r.bottom()) <= 5;
		bool hor = left | right;

		if (hor && bottom) {
			if (left)
				setCursor(Qt::SizeBDiagCursor);
			else
				setCursor(Qt::SizeFDiagCursor);
		} else if (hor) {
			//setCursor(Qt::SizeHorCursor);
		} else if (bottom) {
			//setCursor(Qt::SizeVerCursor);
		} else {
			setCursor(Qt::ArrowCursor);
		}
	}
}

void mainwidget::mouseReleaseEvent(QMouseEvent *e)
{
	mouseDown = false;
}
