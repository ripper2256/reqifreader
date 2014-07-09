#include "datedelegate.h"
#include <QDateTimeEdit>
#include <QDebug>

DateDelegate::DateDelegate()
{
}

QWidget * DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    QDateTimeEdit *dateEdit = new QDateTimeEdit(parent);

    return(dateEdit);
}

void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QVariant data = index.model()->data(index, Qt::DisplayRole);
    QDateTimeEdit *dateEdit = static_cast<QDateTimeEdit*>(editor);
    dateEdit->setDate(data.toDate());
    //spinBox->setValue(data.toInt());
}
