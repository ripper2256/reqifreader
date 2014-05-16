#include "enumdelegate.h"

#include <QComboBox>
#include <QTextDocument>
#include <QPainter>

EnumDelegate::EnumDelegate(const QStringList & texts){
    values = texts;
}

void EnumDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const{
    QStyleOptionViewItemV4 options = option;
    initStyleOption(&options, index);

    painter->save();

    QTextDocument doc;
    doc.setHtml(options.text);
    options.text = "";
    options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &options, painter);

    painter->translate(options.rect.left(), options.rect.top());
    QRect clip(0, 0, options.rect.width(), options.rect.height());
    doc.setTextWidth(options.rect.width());
    doc.drawContents(painter, clip);

    painter->restore();
}

QWidget * EnumDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    QComboBox *cb = new QComboBox(parent);
    cb->addItems(values);
    //te->setFixedHeight(maxHeight+maxHeight/8);
    //te->document()->setDocumentMargin(0);
    //te->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //te->setText(options.text);
    //te->setHtml(options.text);

    return(cb);
}

void EnumDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QVariant data = index.model()->data(index, Qt::DisplayRole);

    QComboBox *te = static_cast<QComboBox*>(editor);

    //te->setHtml(data.toString());

    //qDebug() << foo.toString();
    //QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    //spinBox->setValue(value);
}


void EnumDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QComboBox *te = static_cast<QComboBox*>(editor);
    //spinBox->interpretText();

    //int value = spinBox->value();
    //QString value = te->toHtml();
    //model->setData(index, value, Qt::EditRole);

}
