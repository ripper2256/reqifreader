/*
 * This file is part of the ReqIf Reader.
 *
 *  ReqIf Reader is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ReqIf Reader is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ReqIf Reader.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "htmldelegate.h"

#include <QPainter>
#include <QTextDocument>
#include <QTextEdit>
#include <QDebug>
#include <QAbstractTextDocumentLayout>

/**
 * @brief HTMLDelegate::paint Delegate for showing html formated text
 * @param painter
 * @param option
 * @param index
 */
void HTMLDelegate::paint(QPainter* painter, const QStyleOptionViewItem & option, const QModelIndex &index) const{
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

QWidget * HTMLDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const{
    QTextEdit *te = new QTextEdit(parent);
    //te->setFixedHeight(maxHeight+maxHeight/8);
    //te->document()->setDocumentMargin(0);
    //te->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //te->setText(options.text);
    //te->setHtml(options.text);

    return(te);
}

void HTMLDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    QVariant data = index.model()->data(index, Qt::DisplayRole);

    QTextEdit *te = static_cast<QTextEdit*>(editor);
    //te->setHtml(data.toString());
    te->setHtml(data.toString());
    //qDebug() << data.toString();
    //QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    //spinBox->setValue(value);
}


void HTMLDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QTextEdit *te = static_cast<QTextEdit*>(editor);
    //spinBox->interpretText();

    //int value = spinBox->value();
    QString value = te->toHtml();
    model->setData(index, value, Qt::EditRole);
    //qDebug() << model->data(index, Qt::DisplayRole);
}

void HTMLDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option, const QModelIndex &/* index */) const{
    editor->setGeometry(option.rect);
}

/**
 * @brief HTMLDelegate::sizeHint
 * @param option
 * @param index
 * @return
 */
QSize HTMLDelegate::sizeHint ( const QStyleOptionViewItem & option, const QModelIndex & index ) const{
    QStyleOptionViewItemV4 options = option;
    initStyleOption(&options, index);

    QTextDocument doc;
    doc.setHtml(options.text);
    doc.setTextWidth(options.rect.width());
    return QSize(doc.idealWidth(), doc.size().height());
}
