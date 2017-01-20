#ifndef TITLEBAR2_H
#define TITLEBAR2_H
#include <QtGui>
#include <QFont>
#include <QPixmap>
class TitleBar : public QWidget
{
    Q_OBJECT
private:
    QToolButton *minimize;
    QToolButton *maximize;
    QToolButton *close;
    QPixmap restorePix, maxPix;
    bool maxNormal;
    QPoint startPos;
    QPoint clickPos;
	QLabel* label1;
	QLabel *label;
public:
    TitleBar(QWidget *parent)
    {
        setAutoFillBackground(true);


        setFixedHeight(100);
        setBackgroundRole(QPalette::Highlight);

        minimize = new QToolButton(this);
        maximize = new QToolButton(this);
        close= new QToolButton(this);

        QPixmap pix = style()->standardPixmap(QStyle::SP_TitleBarCloseButton);
        close->setIcon(pix);

        maxPix = style()->standardPixmap(QStyle::SP_TitleBarMaxButton);
        maximize->setIcon(maxPix);

        pix = style()->standardPixmap(QStyle::SP_TitleBarMinButton);
        minimize->setIcon(pix);

         restorePix = style()->standardPixmap(QStyle::SP_TitleBarNormalButton);

      //  minimize->setMinimumHeight(10);
      //  close->setMinimumHeight(10);
      //  maximize->setMinimumHeight(10);
        minimize->setFixedSize(15,15);
        close->setFixedSize(15,15);
        maximize->setFixedSize(15,15);
        label = new QLabel(this);
        /*label->setText("12345");
        parent->setWindowTitle("Window Title2");*/

        QFont ft(QObject::tr("黑体"),18,75);
//        ft.setPointSize(22);
//        ft.setFamily(QObject::tr("黑体"));
        label->setFont(ft);
        QPalette pal;
        pal.setColor(QPalette::WindowText,Qt::white);
        label->setPalette(pal);

        QHBoxLayout *hbox = new QHBoxLayout();
        hbox->addWidget(minimize);
        hbox->addWidget(maximize);
        hbox->addWidget(close);
        hbox->setSpacing(0);
        QVBoxLayout *vbox = new QVBoxLayout();
        vbox->addLayout(hbox);
        vbox->addStretch(3);
        QHBoxLayout *hbox_all = new QHBoxLayout(this);
		//QPixmap pixmap(":/images/xxpt.png");
		label1 = new QLabel( );
		//label1->setPixmap(pixmap);
		label1->setScaledContents(true);
		label1->setMaximumSize(64,64);
		hbox_all->addWidget(label1);
        hbox_all->addWidget(label);
        hbox_all->addLayout(vbox);
        hbox_all->setStretchFactor(label,20);
        //hbox_all->setSpacing(0);
        setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);

        maxNormal = false;

        connect(close, SIGNAL( clicked() ), parent, SLOT(close() ) );
        connect(minimize, SIGNAL( clicked() ), this, SLOT(showSmall() ) );
        connect(maximize, SIGNAL( clicked() ), this, SLOT(showMaxRestore() ) );
    }

public slots:
    void showSmall()
    {
        parentWidget()->showMinimized();
    }

    void showMaxRestore()
    {
        if (maxNormal) {
            parentWidget()->showNormal();
            maxNormal = !maxNormal;
            maximize->setIcon(maxPix);
        } else {
            parentWidget()->showMaximized();
            maxNormal = !maxNormal;
            maximize->setIcon(restorePix);
        }
    }
    void setBackGround()
    {
		QPalette palette;
		QPixmap pixmap(":/images/title.jpg");
		palette.setBrush(this->backgroundRole(), QBrush(pixmap.scaled(this->size(),
			Qt::IgnoreAspectRatio,Qt::SmoothTransformation)));
		setPalette(palette);
    }
public:

	void updateTitle(QString title, QString icon)
	{
		label1->setPixmap(QPixmap(icon));
		label->setText(title);
        //parent->setWindowTitle(title);
	}

protected:
    void mousePressEvent(QMouseEvent *me)
    {
        startPos = me->globalPos();
        clickPos = mapToParent(me->pos());
    }
    void mouseMoveEvent(QMouseEvent *me)
    {
        if (maxNormal)
            return;
        parentWidget()->move(me->globalPos() - clickPos);
    }
    void resizeEvent(QResizeEvent *)
    {
        setBackGround();
    }

};

#endif // TITLEBAR2_H
