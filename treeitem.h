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

#ifndef TREEITEM_H
 #define TREEITEM_H

 #include <QList>
 #include <QVariant>

 class TreeItem
 {
 public:
     TreeItem(const QString &reqifID, const QList<QVariant> &data, const QList<QString> & ref, TreeItem *parent = 0);
     ~TreeItem();

     void appendChild(TreeItem *child);

     TreeItem *child(int row);
     int childCount() const;
     int columnCount() const;
     QVariant data(int column) const;
     int row() const;
     TreeItem *parent();
     void setData(const QList<QVariant> &data);
     bool setData(int column, const QVariant &value);

 private:
     QList<TreeItem*> childItems;
     QList<QVariant> itemData;
     QList<QString> refData;
     QString identifier;
     TreeItem *parentItem;
 };

 #endif
