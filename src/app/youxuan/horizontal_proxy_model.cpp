#include "horizontal_proxy_model.h"

Horizontal_proxy_model::Horizontal_proxy_model(QObject *parent) :
    QAbstractProxyModel(parent)
{
}
QModelIndex Horizontal_proxy_model::mapToSource(const QModelIndex &proxyIndex) const {
  if (sourceModel()) {
    return sourceModel()->index(proxyIndex.column(), proxyIndex.row());
  } else {
    return QModelIndex();
  }
}

QModelIndex Horizontal_proxy_model::mapFromSource(const QModelIndex &sourceIndex) const {
  return index(sourceIndex.column(), sourceIndex.row());
}

QModelIndex Horizontal_proxy_model::index(int row, int column, const QModelIndex &) const {
  return createIndex(row, column, (void*) 0);
}

QModelIndex Horizontal_proxy_model::parent(const QModelIndex &) const {
  return QModelIndex();
}

int Horizontal_proxy_model::rowCount(const QModelIndex &) const {
  return sourceModel() ? sourceModel()->columnCount() : 0;
}

int Horizontal_proxy_model::columnCount(const QModelIndex &) const {
  return sourceModel() ? sourceModel()->rowCount() : 0;
}

QVariant Horizontal_proxy_model::headerData(
           int section, Qt::Orientation orientation, int role) const {
  if (!sourceModel()) { return QVariant(); }
  Qt::Orientation new_orientation = orientation == Qt::Horizontal ?
      Qt::Vertical : Qt::Horizontal;
  return sourceModel()->headerData(section, new_orientation, role);
}
