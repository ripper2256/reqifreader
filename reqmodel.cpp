#include <QtGui>

#include "treeitem.h"
#include "reqmodel.h"

ReqModel::ReqModel(QObject *parent) : QAbstractItemModel(parent){
    QList<QVariant> rootData;
    QList<QString> ref;
    rootItem = new TreeItem("", rootData, ref);
}

ReqModel::~ReqModel(){
    delete rootItem;
}

int ReqModel::columnCount(const QModelIndex &parent) const{
    if (parent.isValid())
        return static_cast<TreeItem*>(parent.internalPointer())->columnCount();
    else
        return rootItem->columnCount();
}

QVariant ReqModel::data(const QModelIndex &index, int role) const{
    if (!index.isValid())
        return QVariant();

    if (role != Qt::DisplayRole && role != Qt::EditRole)
        return QVariant();

    TreeItem *item = static_cast<TreeItem*>(index.internalPointer());

    return item->data(index.column());
}

bool ReqModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (role != Qt::EditRole)
        return false;

    TreeItem *item = getItem(index);
    bool result = item->setData(index.column(), value);

    if (result)
        emit dataChanged(index, index);

    return result;
}

TreeItem *ReqModel::getItem(const QModelIndex &index) const
{
    if (index.isValid()) {
        TreeItem *item = static_cast<TreeItem*>(index.internalPointer());
        if (item) return item;
    }
    return rootItem;
}

Qt::ItemFlags ReqModel::flags(const QModelIndex &index) const{
    if (!index.isValid())
        return 0;

    return Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsEditable;
}

QVariant ReqModel::headerData(int section, Qt::Orientation orientation,
                               int role) const
{
    if (orientation == Qt::Horizontal && role == Qt::DisplayRole)
        return rootItem->data(section);

    return QVariant();
}

QModelIndex ReqModel::index(int row, int column, const QModelIndex &parent)
            const
{
    if (!hasIndex(row, column, parent))
        return QModelIndex();

    TreeItem *parentItem;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    TreeItem *childItem = parentItem->child(row);
    if (childItem)
        return createIndex(row, column, childItem);
    else
        return QModelIndex();
}

QModelIndex ReqModel::parent(const QModelIndex &index) const
{
    if (!index.isValid())
        return QModelIndex();

    TreeItem *childItem = static_cast<TreeItem*>(index.internalPointer());
    TreeItem *parentItem = childItem->parent();

    if (parentItem == rootItem)
        return QModelIndex();

    return createIndex(parentItem->row(), 0, parentItem);
}

int ReqModel::rowCount(const QModelIndex &parent) const
{
    TreeItem *parentItem;
    if (parent.column() > 0)
        return 0;

    if (!parent.isValid())
        parentItem = rootItem;
    else
        parentItem = static_cast<TreeItem*>(parent.internalPointer());

    return parentItem->childCount();
}


bool ReqModel::setHeaderData(const QStringList &headers){
    QList<QVariant> rootData;
        foreach (QString header, headers)
            rootData << header;

    bool result = true;
    rootItem->setData(rootData);

    return result;
}


TreeItem *ReqModel::setupModelData(const QString &reqifID, const QList<QVariant> &columnData,const QList<QString> &refData, TreeItem *parent){
    if(parent == 0)
        parent = rootItem;
    QList<TreeItem*> parents;
    parents << parent;
    TreeItem *item = new TreeItem(reqifID, columnData, refData, parents.last());
    parents.last()->appendChild(item);
    return item;
}
