#ifndef INTDELEGATE_H
#define INTDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QSpinBox>

class IntDelegate : public QStyledItemDelegate
{
public:
    IntDelegate();
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // INTDELEGATE_H
