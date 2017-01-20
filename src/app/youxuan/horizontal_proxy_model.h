#ifndef HORIZONTAL_PROXY_MODEL_H
#define HORIZONTAL_PROXY_MODEL_H

#include <QAbstractProxyModel>

class Horizontal_proxy_model : public QAbstractProxyModel
{
    Q_OBJECT
public:
    explicit Horizontal_proxy_model(QObject *parent = 0);

    QModelIndex mapToSource(const QModelIndex &proxyIndex) const;
      QModelIndex mapFromSource(const QModelIndex &sourceIndex) const;
      QModelIndex index(int row, int column, const QModelIndex &parent = QModelIndex()) const;
      QModelIndex parent(const QModelIndex &child) const;
      int rowCount(const QModelIndex &parent) const;
      int columnCount(const QModelIndex &parent) const;
      QVariant headerData(int section, Qt::Orientation orientation, int role) const;

};

#endif // HORIZONTAL_PROXY_MODEL_H
