#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include <QStyledItemDelegate>
#include <QPainter>
#include <QSpinBox>

class DateDelegate : public QStyledItemDelegate
{
public:
    DateDelegate();
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    QWidget * createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
};

#endif // DATEDELEGATE_H
