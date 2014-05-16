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
