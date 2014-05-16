#ifndef REQMODEL_H
#define REQMODEL_H

#include <QAbstractItemModel>
#include <QModelIndex>
#include <QVariant>
#include "treeitem.h"

class ReqModel;

class ReqModel : public QAbstractItemModel
{


public:
    ReqModel(QObject *parent = 0);
    ~ReqModel();

    QVariant data(const QModelIndex &index, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    QModelIndex index(int row, int column,
                      const QModelIndex &parent = QModelIndex()) const;
    QModelIndex parent(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    TreeItem *setupModelData(const QString &reqifID, const QList<QVariant> &columnData,const QList<QString> &refData, TreeItem *parent = 0);
    bool setHeaderData(const QStringList &headers);

private:
    TreeItem *getItem(const QModelIndex &index) const;
    TreeItem *rootItem;
};

#endif // REQMODEL_H
