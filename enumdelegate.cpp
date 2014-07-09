#include "enumdelegate.h"
#include "enumvalue.h"

#include <QComboBox>
#include <QTextDocument>
#include <QPainter>
#include <QDebug>

#include <QListWidget>
#include <QListWidgetItem>

EnumDelegate::EnumDelegate(const QStringList & texts){
    values = texts;
}

void EnumDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const{
    QStyleOptionViewItemV4 options = option;
    initStyleOption(&options, index);
    QVariant data = index.model()->data(index, Qt::DisplayRole);
    QStringList str = data.toStringList();
    painter->save();

    QTextDocument doc;
    doc.setPlainText(str.join("\n"));

    options.text = "";
    options.widget->style()->drawControl(QStyle::CE_ItemViewItem, &options, painter);

    painter->translate(options.rect.left(), options.rect.top());
    QRect clip(0, 0, options.rect.width(), options.rect.height());
    doc.setTextWidth(options.rect.width());
    doc.drawContents(painter, clip);

    painter->restore();
}

QWidget * EnumDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    //QComboBox *cb = new QComboBox(parent);
    //cb->addItems(values);
    //return(cb);
    QVariant data = index.model()->data(index, Qt::DisplayRole);
    QStringList str = data.toStringList();

    QListWidget *listWidget = new QListWidget(parent);

    //listWidget->setSelectionBehavior();

    QStringListIterator it(values);
    while (it.hasNext()){
        QString value = it.next();
        QListWidgetItem *listItem = new QListWidgetItem(value,listWidget);
        if(str.contains(value,Qt::CaseSensitive)){
            listItem->setCheckState(Qt::Checked);
        } else {
            listItem->setCheckState(Qt::Unchecked);
        }
        listWidget->addItem(listItem);
    }
    return listWidget;

}

void EnumDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    //QVariant data = index.model()->data(index, Qt::DisplayRole);
    //QStringList str = data.toStringList();
    //QComboBox *te = static_cast<QComboBox*>(editor);

    /*QListWidget *listWidget = static_cast<QListWidget*>(editor);
    for(int i=0;i<listWidget->count;i++){
        QListWidgetItem *listItem = listWidget->item(i);
        listItem->setCheckState(Qt::Checked);
    }*/
    /*QVariant data = index.model()->data(index, Qt::DisplayRole);
    EnumValue enumValue = qvariant_cast<EnumValue>(data);
    qDebug() << enumValue.getLongName();*/
}


void EnumDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QListWidget *listWidget = static_cast<QListWidget*>(editor);
    QStringList str;
    for(int i=0;i<listWidget->count();i++){
        QListWidgetItem *listItem = listWidget->item(i);
        if(listItem->checkState() == Qt::Checked){
            str.append(listItem->text());
        }
    }
    model->setData(index, str, Qt::EditRole);
}

QSize EnumDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const{
    QVariant data = index.model()->data(index, Qt::DisplayRole);
    //QFont font = QApplication::font();
    //qDebug() << option.;
    //return QSize(doc.idealWidth(), doc.size().height());
    return QSize(200,80);
}
