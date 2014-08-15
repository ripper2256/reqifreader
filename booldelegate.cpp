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
#include "booldelegate.h"
#include <QComboBox>
#include <QTextDocument>
#include <QPainter>
#include <QDebug>


BoolDelegate::BoolDelegate(){
    values.append("true");
    values.append("false");
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
