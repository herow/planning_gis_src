#ifndef COMBOBOXDELEGATE_H
#define COMBOBOXDELEGATE_H

#include <QStyledItemDelegate>

class ComboBoxDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    //ComboBoxDelegate(QObject *parent=0) : QStyledItemDelegate(parent){}
    ComboBoxDelegate(QObject *aParent = 0)
        : QStyledItemDelegate(aParent)
    {}
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor,
                      QAbstractItemModel *model,
                      const QModelIndex &index) const;

};

#endif // COMBOBOXDELEGATE_H
