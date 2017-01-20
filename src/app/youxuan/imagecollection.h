#ifndef IMAGECOLLECTION_H
#define IMAGECOLLECTION_H

#include <QWidget>

namespace Ui {
class ImageCollection;
}

class ImageCollection : public QWidget
{
    Q_OBJECT

public:
    explicit ImageCollection(QWidget *parent = 0);
    ~ImageCollection();

private:
    Ui::ImageCollection *ui;
};

#endif // IMAGECOLLECTION_H
