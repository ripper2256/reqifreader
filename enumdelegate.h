#ifndef ENUMDELEGATE_H
#define ENUMDELEGATE_H

#include <QStyledItemDelegate>

class EnumDelegate : public QStyledItemDelegate
{
public:
    EnumDelegate(const QStringList & texts);
    void paint ( QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index ) const;
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;
private:
    QStringList values;
};

#endif // ENUMDELEGATE_H
