/****************************************************************************
**
** Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
** Contact: http://www.qt-project.org/legal
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** You may use this file under the terms of the BSD license as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of Digia Plc and its Subsidiary(-ies) nor the names
**     of its contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "informationwindow.h"
#include "imageitem.h"
#include "view.h"
#include "qgsapplication.h"
//! [0]
View::View(const QString &pictable,const QString &xiang, const QString &cun, QWidget *parent)
    : QGraphicsView(parent)
{
    setAttribute(Qt::WA_DeleteOnClose);

	 QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
	QTextCodec *codec =QTextCodec::codecForName("gbk");

    picturetable = new QSqlTableModel(this);

    const char * strCunname = "村名称";
    const char * strXiangname = "乡名称";
    QString cunName=QString::fromLocal8Bit(strCunname);
    QString xiangName=QString::fromLocal8Bit(strXiangname);

    QString fullSql = QString( " `%1`='%2' and `%3`='%4'" )
            .arg(cunName).arg(cun)
            .arg(xiangName).arg(xiang);

    picturetable->setTable(pictable);
    picturetable->setFilter(fullSql);
    picturetable->select();
//! [0]

//! [1]
    scene = new QGraphicsScene(this);
    scene->setSceneRect(0, 0, 465, 555);
    setScene(scene);

    addItems();

//    QGraphicsPixmapItem *logo = scene->addPixmap(QPixmap("./logo.png"));
//    logo->setPos(30, 515);

#if !defined(Q_OS_SYMBIAN) && !defined(Q_WS_MAEMO_5)
    setMinimumSize(470, 560);
    setMaximumSize(470, 560);
#else
    setDragMode(QGraphicsView::ScrollHandDrag);
#endif

//   setWindowTitle(tr("Offices World Wide"));
}
//! [1]
View::~View()
{
     delete scene;
     delete picturetable;
     qDeleteAll(informationWindows);
     informationWindows.clear();
}
//! [3]
void View::addItems()
{
    int officeCount = picturetable->rowCount();

    int imageOffset = 150;
    int leftMargin = 70;
    int topMargin = 40;

    for (int i = 0; i < officeCount; i++) {
        ImageItem *image;
        QGraphicsTextItem *label;
        QSqlRecord record = picturetable->record(i);

        //int id = record.value("id").toInt();
		int id = i;
        QString file = record.value(4).toString();
        QString location = record.value(2).toString();

        int columnOffset = ((i % 2) * 37);
        int y = ((i / 2) * imageOffset) + topMargin ;
        int x = ((i % 2) * imageOffset) + leftMargin + columnOffset;

        image = new ImageItem(id, QPixmap(QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\pic\\") + file));
        image->setData(0, i);
        image->setPos(x, y);
        scene->addItem(image);

        label = scene->addText(location);
        QPointF labelOffset((150 - label->boundingRect().width()) / 2, 120.0);
        label->setPos(QPointF(x, y) + labelOffset);
    }
}
//! [3]

//! [5]
void View::mouseReleaseEvent(QMouseEvent *event)
{
    if (QGraphicsItem *item = itemAt(event->pos())) {
        if (ImageItem *image = qgraphicsitem_cast<ImageItem *>(item))
            showInformation(image);
    }
    QGraphicsView::mouseReleaseEvent(event);
}
//! [5]

//! [6]
void View::showInformation(ImageItem *image)
{
    int id = image->id();
    if (id < 0 || id >= picturetable->rowCount())
        return;

    InformationWindow *window = findWindow(id);
    if (window && window->isVisible()) {
        window->raise();
        window->activateWindow();
    } else if (window && !window->isVisible()) {
#ifndef Q_OS_SYMBIAN
        window->show();
#else
        window->showMaximized();
#endif
    } else {
        InformationWindow *window;
        window = new InformationWindow(id, picturetable, this);

        connect(window, SIGNAL(imageChanged(int,QString)),
                this, SLOT(updateImage(int,QString)));

#ifndef Q_OS_SYMBIAN
        window->move(pos() + QPoint(20, 40));
        window->show();
#else
        window->showMaximized();
#endif
        informationWindows.append(window);
    }
}
//! [6]

//! [7]
void View::updateImage(int id, const QString &fileName)
{
    QList<QGraphicsItem *> items = scene->items();

    while(!items.empty()) {
        QGraphicsItem *item = items.takeFirst();

        if (ImageItem *image = qgraphicsitem_cast<ImageItem *>(item)) {
            if (image->id() == id){
                image->setPixmap(QPixmap(":/" +fileName));
                image->adjust();
                break;
            }
        }
    }
}
//! [7]

//! [8]
InformationWindow* View::findWindow(int id)
{
    QList<InformationWindow*>::iterator i, beginning, end;

    beginning = informationWindows.begin();
    end = informationWindows.end();

    for (i = beginning; i != end; ++i) {
        InformationWindow *window = (*i);
        if (window && (window->id() == id))
            return window;
    }
    return 0;
}
//! [8]

