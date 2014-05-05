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
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    TreeItem *setupModelData(const QList<QVariant> &columnData, TreeItem *parent = 0);
    bool setHeaderData(const QStringList &headers);

private:
    //void setupModelData(const QStringList &lines, TreeItem *parent);

    TreeItem *rootItem;
};

#endif // REQMODEL_H
