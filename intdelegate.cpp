#include "intdelegate.h"
#include <limits>
#include <QtDebug>

IntDelegate::IntDelegate()
{
}


QWidget * IntDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    QSpinBox *sb = new QSpinBox(parent);
    sb->setRange(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
    return(sb);
}

void IntDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QVariant data = index.model()->data(index, Qt::DisplayRole);
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(data.toInt());
}
