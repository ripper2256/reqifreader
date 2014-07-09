#ifndef BOOLDELEGATE_H
#define BOOLDELEGATE_H

#include <QStyledItemDelegate>

class BoolDelegate : public QStyledItemDelegate
{


public:
    BoolDelegate();
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private:
    QStringList values;
};

#endif // BOOLDELEGATE_H
