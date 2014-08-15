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
