#include "booldelegate.h"
#include <QComboBox>
#include <QTextDocument>
#include <QPainter>
#include <QDebug>


BoolDelegate::BoolDelegate(){
    values.append("true");
    values.append("false");
}


void BoolDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const{
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

QWidget * BoolDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    QComboBox *cb = new QComboBox(parent);
    cb->addItems(values);

    return(cb);
}

void BoolDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QVariant data = index.model()->data(index, Qt::DisplayRole);
    QComboBox *te = static_cast<QComboBox*>(editor);
    bool qData = data.toBool();
    te->setCurrentIndex(qData ? 0 : 1);
}


void BoolDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QComboBox *te = static_cast<QComboBox*>(editor);
    bool data = te->currentText() == "true" ? true : false;

    model->setData(index, data, Qt::EditRole);
}
