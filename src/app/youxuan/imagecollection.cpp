#include "imagecollection.h"
#include "ui_imagecollection.h"

ImageCollection::ImageCollection(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ImageCollection)
{
    ui->setupUi(this);
}

ImageCollection::~ImageCollection()
{
    delete ui;
}
