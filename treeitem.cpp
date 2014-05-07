#include <QStringList>

#include "treeitem.h"

TreeItem::TreeItem(const QString &reqifID, const QList<QVariant> &data, const QList<QString> & ref, TreeItem *parent){
    identifier = reqifID;
    parentItem = parent;
    itemData = data;
    refData = ref;
}

TreeItem::~TreeItem()
{
    qDeleteAll(childItems);
}

void TreeItem::setData(const QList<QVariant> &data){
    itemData = data;
}

void TreeItem::appendChild(TreeItem *item)
{
    childItems.append(item);
}

TreeItem *TreeItem::child(int row)
{
    return childItems.value(row);
}

int TreeItem::childCount() const
{
    return childItems.count();
}

int TreeItem::columnCount() const
{
    return itemData.count();
}

QVariant TreeItem::data(int column) const
{
    return itemData.value(column);
}

TreeItem *TreeItem::parent()
{
    return parentItem;
}

int TreeItem::row() const
{
    if (parentItem)
        return parentItem->childItems.indexOf(const_cast<TreeItem*>(this));

    return 0;
}
