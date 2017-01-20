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

#include "mainwindow2.h"
//#include "dialog.h"

#include <QtGui>
#include <QtSql>
//#include <QtXml>
#include "qgsapplication.h"

#include <sqlite3.h>



extern int uniqueAlbumId;
extern int uniqueArtistId;

MainWindow2::MainWindow2(QWidget *parent)
     : QMainWindow(parent)
{
//    file = albumDetails;
//    readAlbumData();

    model = new QSqlTableModel;

    QTextCodec::setCodecForLocale(QTextCodec::codecForName("gbk"));
    codec =QTextCodec::codecForName("gbk");
    const char * strtablename = "微观形态设计";
    QString tablename=QString::fromLocal8Bit(strtablename);



    const char * c_combo1 = "用地布局";
    const char * c_type = "类型";
    QString str_combo1=QString::fromLocal8Bit(c_combo1);
    QString str_type=QString::fromLocal8Bit(c_type);
    QString fullSql = QString( " `%1`='%2'" )
                  .arg(str_type).arg(str_combo1);
    model->setTable(tablename);
    model->setFilter(fullSql);
    model->select();

    QGroupBox *artists = createArtistGroupBox();
    QGroupBox *albums = createAlbumGroupBox();
    QGroupBox *details = createDetailsGroupBox();

    //artistView->setCurrentIndex(0);
//    uniqueAlbumId = model->rowCount();
//    uniqueArtistId = artistView->count();

    connect(model, SIGNAL(rowsInserted(QModelIndex,int,int)),
            this, SLOT(updateHeader(QModelIndex,int,int)));
    connect(model, SIGNAL(rowsRemoved(QModelIndex,int,int)),
            this, SLOT(updateHeader(QModelIndex,int,int)));

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(artists, 0, 0);
    layout->addWidget(albums, 1, 0);
    layout->addWidget(details, 0, 1, 2, 1);
#if !defined(Q_OS_SYMBIAN) && !defined(Q_WS_MAEMO_5)
    layout->setColumnStretch(1, 1);
    layout->setColumnMinimumWidth(1, 500);

    layout->setColumnStretch(0, 1);
    layout->setColumnMinimumWidth(0, 200);
#endif

    QWidget *widget = new QWidget;
    widget->setLayout(layout);
    setCentralWidget(widget);
  //  createMenuBar();

  //  showImageLabel();
#if !defined(Q_OS_SYMBIAN) && !defined(Q_WS_MAEMO_5)
    resize(850, 400);
#endif
    setWindowTitle(tablename);
}
MainWindow2::~MainWindow2()
{
    delete model;
    delete albumView;
    delete artistView;


    delete detailLabel;
    delete imageLabel;
    delete profileLabel;
    delete titleLabel;





}
void MainWindow2::changeArtist(int row)
{
    const char * c_type = "类型";
    //QString str_combo1=QString::fromLocal8Bit(c_combo1);
    QString str_type=QString::fromLocal8Bit(c_type);
    QString fullSql = QString( " `%1`='%2'" )
                  .arg(str_type).arg(artistView->currentText());

    model->setFilter(fullSql);
    QModelIndex index = model->index(0,0);
    showArtistProfile(index);
     albumView->selectRow(0);

//    if (row > 0) {
//        QModelIndex index = model->relationModel(2)->index(row, 1);
//        model->setFilter("artist = '" + index.data().toString() + '\'') ;
//        showArtistProfile(index);
//    } else if (row == 0) {
//        model->setFilter(QString());
//        showImageLabel();
//    } else {
//        return;
//    }
}

void MainWindow2::showArtistProfile(QModelIndex index)
{
//    QSqlRecord record = model->relationModel(2)->record(index.row());

//    QString name = record.value("artist").toString();
//    QString count = record.value("albumcount").toString();
//    profileLabel->setText(tr("Artist : %1 \n" \
//                             "Number of Albums: %2").arg(name).arg(count));

//    profileLabel->show();
//    iconLabel->show();

//    titleLabel->hide();
//    trackList->hide();
//    imageLabel->hide();
    QModelIndex detailIndex=model->index(index.row(),index.column()+3);

    QImage img;
    if(! ( img.load(QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\") + model->data(detailIndex, Qt::EditRole).toString()) ) )  
    {
        QMessageBox::information(this,
                                 tr("warning"),
                                 tr("unable to load image!"));

        return ;
    }
    QImage imgScaled;
    imgScaled=img.scaled(700,700,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    imageLabel->setPixmap(QPixmap::fromImage(imgScaled));

}

void MainWindow2::showAlbumDetails(QModelIndex index)
{
    QModelIndex detailIndex=model->index(index.row(),index.column()+3);

    QImage img;
    if(! ( img.load(QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\") + model->data(detailIndex, Qt::EditRole).toString()) ) )
    {
        QMessageBox::information(this,
                                 tr("warning"),
                                 tr("unable to load image!"));

        return ;
    }
    QImage imgScaled;
    imgScaled=img.scaled(700,700,Qt::KeepAspectRatio,Qt::SmoothTransformation);

    imageLabel->setPixmap(QPixmap::fromImage(imgScaled));

//    detailIndex=model->index(index.row(),index.column()+2);
//    detailLabel->adjustSize();
//    detailLabel->setWordWrap(true);
//    detailLabel->setAlignment(Qt::AlignTop);
//    detailLabel->setText(model->data(detailIndex, Qt::EditRole).toString());

}

//void MainWindow2::getTrackList(QDomNode album)
//{
//    trackList->clear();

//    QDomNodeList tracks = album.childNodes();
//    QDomNode track;
//    QString trackNumber;

//    for (int j = 0; j < tracks.count(); j++) {

//        track = tracks.item(j);
//        trackNumber = track.toElement().attribute("number");

//        QListWidgetItem *item = new QListWidgetItem(trackList);
//        item->setText(trackNumber + ": " + track.toElement().text());
//    }
//}

void MainWindow2::addAlbum()
{
//    Dialog *dialog = new Dialog(model, albumData, file, this);
//    int accepted = dialog->exec();

//    if (accepted == 1) {
//        int lastRow = model->rowCount() - 1;
//        albumView->selectRow(lastRow);
//        albumView->scrollToBottom();
//        showAlbumDetails(model->index(lastRow, 0));
//    }
}

void MainWindow2::deleteAlbum()
{
    QModelIndexList selection = albumView->selectionModel()->selectedRows(0);

    if (!selection.empty()) {
        QModelIndex idIndex = selection.at(0);
        int id = idIndex.data().toInt();
        QString title = idIndex.sibling(idIndex.row(), 1).data().toString();
        QString artist = idIndex.sibling(idIndex.row(), 2).data().toString();

        QMessageBox::StandardButton button;
        button = QMessageBox::question(this, tr("Delete Album"),
                                       tr("Are you sure you want to "
                                          "delete '%1' by '%2'?")
                                       .arg(title, artist),
                                       QMessageBox::Yes | QMessageBox::No);

        if (button == QMessageBox::Yes) {
            removeAlbumFromFile(id);
            removeAlbumFromDatabase(idIndex);
            decreaseAlbumCount(indexOfArtist(artist));

            showImageLabel();
        }
    } else {
        QMessageBox::information(this, tr("Delete Album"),
                                 tr("Select the album you want to delete."));
    }
}

void MainWindow2::removeAlbumFromFile(int id)
{

//    QDomNodeList albums = albumData.elementsByTagName("album");

//    for (int i = 0; i < albums.count(); i++) {
//        QDomNode node = albums.item(i);
//        if (node.toElement().attribute("id").toInt() == id) {
//            albumData.elementsByTagName("archive").item(0).removeChild(node);
//            break;
//        }
//    }
/*
    The following code is commented out since the example uses an in
    memory database, i.e., altering the XML file will bring the data
    out of sync.

    if (!file->open(QIODevice::WriteOnly)) {
        return;
    } else {
        QTextStream stream(file);
        albumData.elementsByTagName("archive").item(0).save(stream, 4);
        file->close();
    }
*/
}

void MainWindow2::removeAlbumFromDatabase(QModelIndex index)
{
    model->removeRow(index.row());
}

void MainWindow2::decreaseAlbumCount(QModelIndex artistIndex)
{
//    int row = artistIndex.row();
//    QModelIndex albumCountIndex = artistIndex.sibling(row, 2);
//    int albumCount = albumCountIndex.data().toInt();

//    QSqlTableModel *artists = model->relationModel(2);

//    if (albumCount == 1) {
//        artists->removeRow(row);
//        showImageLabel();
//    } else {
//        artists->setData(albumCountIndex, QVariant(albumCount - 1));
//    }
}

void MainWindow2::readAlbumData()
{
//    if (!file->open(QIODevice::ReadOnly))
//        return;

//    if (!albumData.setContent(file)) {
//        file->close();
//        return;
//    }
//    file->close();
}

QGroupBox* MainWindow2::createArtistGroupBox()
{
    /*const char * c_combo1 = "公共设施配置";
    const char * c_combo2 = "用地布局";
    QString str_combo1=QString::fromLocal8Bit(c_combo1);
    QString str_combo2=QString::fromLocal8Bit(c_combo2);*/

    artistView = new QComboBox;
    //artistView->addItem(str_combo2);
    //artistView->addItem(str_combo1);
	sqlite3      *myDatabase;
	const char   *myTail;
	sqlite3_stmt *myPreparedStatement;
	int           myResult;
	//check the db is available
	myResult = sqlite3_open_v2( (QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\db\\test.db")).toUtf8().data(), &myDatabase, SQLITE_OPEN_READONLY, NULL );
	if ( myResult != SQLITE_OK )
	{
		Q_ASSERT( myResult == SQLITE_OK );
	}
	QString mySql = QString::fromLocal8Bit("select distinct 类型 from 微观形态设计");
	myResult = sqlite3_prepare( myDatabase, mySql.toUtf8(), mySql.toUtf8().length(), &myPreparedStatement, &myTail );
	// XXX Need to free memory from the error msg if one is set
	if ( myResult == SQLITE_OK )
	{
		int i=0;
		while ( sqlite3_step( myPreparedStatement ) == SQLITE_ROW )
		{
			artistView->insertItem(i,QString::fromUtf8(( char* ) sqlite3_column_text( myPreparedStatement, 0 )));
			i++;
		}
	}

	sqlite3_finalize( myPreparedStatement );
	sqlite3_close( myDatabase );

    artistView->setCurrentIndex(artistView->findText(QString::fromLocal8Bit("用地布局")));

    connect(artistView, SIGNAL(currentIndexChanged(int)),
            this, SLOT(changeArtist(int)));
    const char * strtablename = "类型";
    QString type=QString::fromLocal8Bit(strtablename);
    QGroupBox *box = new QGroupBox(type);

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(artistView, 0, 0);
    box->setLayout(layout);

   return box;
}

QGroupBox* MainWindow2::createAlbumGroupBox()
{
    const char * c_type = "内容";
    //QString str_combo1=QString::fromLocal8Bit(c_combo1);
    QString str_type=QString::fromLocal8Bit(c_type);
    QGroupBox *box = new QGroupBox(str_type);

    albumView = new QTableView;
    albumView->setEditTriggers(QAbstractItemView::NoEditTriggers);
//    albumView->setSortingEnabled(true);
    albumView->setSelectionBehavior(QAbstractItemView::SelectRows);
    albumView->setSelectionMode(QAbstractItemView::SingleSelection);
    albumView->setShowGrid(false);
    albumView->verticalHeader()->hide();
    albumView->setAlternatingRowColors(true);
    albumView->setModel(model);
    albumView->hideColumn(1);
    albumView->hideColumn(2);
    albumView->hideColumn(3);
   // albumView->resizeColumnToContents(0);
    albumView->setColumnWidth(0,150);


//    QLocale locale = albumView->locale();
//    locale.setNumberOptions(QLocale::OmitGroupSeparator);
//    albumView->setLocale(locale);

    connect(albumView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(showAlbumDetails(QModelIndex)));
    connect(albumView, SIGNAL(activated(QModelIndex)),
            this, SLOT(showAlbumDetails(QModelIndex)));

    QHBoxLayout *layout = new QHBoxLayout;
    layout->addWidget(albumView, 0, 0);


//    detailLabel =new QLabel;
//    detailLabel->setText("Content:");
//    detailLabel->setMinimumWidth(300);

//    layout->addWidget(detailLabel,0,0);
    box->setLayout(layout);
    albumView->selectRow(0);
    return box;
}

QGroupBox* MainWindow2::createDetailsGroupBox()
{
    const char * c_type = "设计图";
    //QString str_combo1=QString::fromLocal8Bit(c_combo1);
    QString str_type=QString::fromLocal8Bit(c_type);
    QGroupBox *box = new QGroupBox(str_type);


//    profileLabel = new QLabel;
//    profileLabel->setWordWrap(true);
//    profileLabel->setAlignment(Qt::AlignBottom);

//    titleLabel = new QLabel;
//    titleLabel->setWordWrap(true);
//    titleLabel->setAlignment(Qt::AlignBottom);

//    iconLabel = new QLabel();
//    iconLabel->setAlignment(Qt::AlignBottom | Qt::AlignRight);
//    iconLabel->setPixmap(QPixmap(":/images/icon.png"));

    imageLabel = new QLabel;
    imageLabel->setWordWrap(true);
    imageLabel->setAlignment(Qt::AlignCenter);
//    imageLabel->setScaledContents(true);
    imageLabel->setMaximumWidth(700);
    QModelIndex detailIndex=model->index(0 ,3);
	QString text = QString::fromLocal8Bit("\\data\\") + model->data(detailIndex, Qt::EditRole).toString();
	//QMessageBox::information(NULL, "Title", text, QMessageBox::Yes | QMessageBox::No, QMessageBox::Yes);

    QImage img;
    if(! ( img.load(QgsApplication::pkgDataPath() + QString::fromLocal8Bit("\\data\\") + model->data(detailIndex, Qt::EditRole).toString()) ) ) //加载图像
    {
        QMessageBox::information(this,
                                 tr("warning"),
                                 tr("unable to load image!"));

        return 0;
    }
    QImage imgScaled;
    imgScaled=img.scaled(700,700,Qt::KeepAspectRatio,Qt::SmoothTransformation);
//    QPixmap image = QPixmap("./"+model->data(detailIndex, Qt::EditRole).toString());
//    tempPix.scaled(QSize(490, 300), Qt::KeepAspectRatio);
    imageLabel->setPixmap(QPixmap::fromImage(imgScaled));
   // imageLabel->setPixmap(QPixmap("./"+model->data(detailIndex, Qt::EditRole).toString()));

  //  trackList = new QListWidget;

    QGridLayout *layout = new QGridLayout;
    layout->addWidget(imageLabel, 0, 0);
//    layout->addWidget(imageLabel, 0, 0, 3, 2);
//    layout->addWidget(profileLabel, 0, 0);
//    layout->addWidget(iconLabel, 0, 1);
//    layout->addWidget(titleLabel, 1, 0, 1, 2);
//    layout->addWidget(trackList, 2, 0, 1, 2);
//    layout->setRowStretch(2, 1);
    box->setLayout(layout);

    return box;
}

void MainWindow2::createMenuBar()
{
    QAction *addAction = new QAction(tr("&Add album..."), this);
    QAction *deleteAction = new QAction(tr("&Delete album..."), this);
    QAction *quitAction = new QAction(tr("&Quit"), this);
    QAction *aboutAction = new QAction(tr("&About"), this);
    QAction *aboutQtAction = new QAction(tr("About &Qt"), this);

    addAction->setShortcut(tr("Ctrl+A"));
    deleteAction->setShortcut(tr("Ctrl+D"));
    quitAction->setShortcuts(QKeySequence::Quit);

    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(addAction);
    fileMenu->addAction(deleteAction);
    fileMenu->addSeparator();
    fileMenu->addAction(quitAction);

    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAction);
    helpMenu->addAction(aboutQtAction);

    connect(addAction, SIGNAL(triggered(bool)), this, SLOT(addAlbum()));
    connect(deleteAction, SIGNAL(triggered(bool)), this, SLOT(deleteAlbum()));
    connect(quitAction, SIGNAL(triggered(bool)), this, SLOT(close()));
    connect(aboutAction, SIGNAL(triggered(bool)), this, SLOT(about()));
    connect(aboutQtAction, SIGNAL(triggered(bool)), qApp, SLOT(aboutQt()));
}

void MainWindow2::showImageLabel()
{
//    profileLabel->hide();
//    titleLabel->hide();
//    iconLabel->hide();
//    trackList->hide();

  //  imageLabel->show();
}

QModelIndex MainWindow2::indexOfArtist(const QString &artist)
{
//    QSqlTableModel *artistModel = model->relationModel(2);

//    for (int i = 0; i < artistModel->rowCount(); i++) {
//        QSqlRecord record =  artistModel->record(i);
//        if (record.value("artist") == artist)
//            return artistModel->index(i, 1);
//    }
    return QModelIndex();
}

void MainWindow2::updateHeader(QModelIndex, int, int)
{
    adjustHeader();
}

void MainWindow2::adjustHeader()
{
//    albumView->hideColumn(0);
//    albumView->horizontalHeader()->setResizeMode(1, QHeaderView::Stretch);
//    albumView->resizeColumnToContents(2);
//    albumView->resizeColumnToContents(3);
}

void MainWindow2::about()
{
    QMessageBox::about(this, tr("About Music Archive"),
            tr("<p>The <b>Music Archive</b> example shows how to present "
               "data from different data sources in the same application. "
               "The album titles, and the corresponding artists and release dates, "
               "are kept in a database, while each album's tracks are stored "
               "in an XML file. </p><p>The example also shows how to add as "
               "well as remove data from both the database and the "
               "associated XML file using the API provided by the QtSql and "
               "QtXml modules, respectively.</p>"));
}
