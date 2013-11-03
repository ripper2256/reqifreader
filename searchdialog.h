#ifndef SEARCHDIALOG_H
#define SEARCHDIALOG_H

#include <QDialog>
#include <QTreeWidget>

namespace Ui {
class SearchDialog;
}

class SearchDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SearchDialog(QWidget *parent = 0, QTreeWidget *tree = 0);
    ~SearchDialog();

private slots:
    void search();
    void next();
    void prev();

private:
    Ui::SearchDialog *ui;
    QTreeWidget *treeWidget;
    int currentPosition;
    QList <QTreeWidgetItem *> searchResults;
};

#endif // SEARCHDIALOG_H
