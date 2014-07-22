/*
 * This file is part of the ReqIf Reader.
 *
 *  ReqIf Reader is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ReqIf Reader is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ReqIf Reader.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "domparser.h"
#include "searchdialog.h"
#include "spectypesoverviewdialog.h"
#include "rifparser.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;

private slots:
    void open();
    void about();
    void info();
    void save();
    void search();
    void switchView();
    void switchMerge();
    void showSpecTypes();
    void showContextMenu(QTreeWidgetItem* item, const QPoint& globalPos);
    void onCustomContextMenuRequested(const QPoint& pos);
    void getSelectedElement(const QModelIndex &index);

private:
    void openXmlFile();

    Parser *parser = NULL;
    SearchDialog *searchDialog = NULL;
    SpecTypesOverviewDialog *specTypeOverview = NULL;

    bool listView;
    bool mergeTextAndChapter;
    QString fileName;
};

#endif // MAINWINDOW_H
