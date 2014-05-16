#include "intdelegate.h"
#

IntDelegate::IntDelegate()
{
}


QWidget * IntDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    QSpinBox *sb = new QSpinBox(parent);
    //te->setFixedHeight(maxHeight+maxHeight/8);
    //te->document()->setDocumentMargin(0);
    //te->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //te->setText(options.text);
    //te->setHtml(options.text);

    return(sb);
}

void IntDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QVariant data = index.model()->data(index, Qt::DisplayRole);

    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(data.toInt());
}
