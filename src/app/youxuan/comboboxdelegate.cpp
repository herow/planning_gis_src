#include "comboboxdelegate.h"
#include <QComboBox>

void ComboBoxDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
       if(index.column() ==6||index.column() == 7||index.column() == 11) 
       {
           QComboBox *comboEditor = qobject_cast<QComboBox *>(editor);
           if (comboEditor)
           {
               int i = comboEditor->findText(index.model()->data(index, Qt::EditRole).toString()); 
               comboEditor->setCurrentIndex(i); 
           }
       }
       else
       {
           return QStyledItemDelegate::setEditorData(editor, index);
       }
}
void ComboBoxDelegate::setModelData(QWidget *editor,
                  QAbstractItemModel *model,
                  const QModelIndex &index) const
{
       if(index.column() ==6||index.column() == 7||index.column() == 11)
       {
           QComboBox *comboBox = qobject_cast<QComboBox *>(editor);
           if(comboBox)
           {
               model->setData(index, comboBox->currentText());
           }
       }
       else
       {
           return QStyledItemDelegate::setModelData(editor, model, index);
       }
}
