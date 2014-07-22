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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "infodialog.h"
#include "reqifxmlwriter.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QErrorMessage>
#include <QPushButton>
#include <QDebug>

/**
 * @brief MainWindow::MainWindow constructor
 * @param parent
 */
MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    //ui->treeWidget->setContextMenuPolicy(Qt::CustomContextMenu);
    //connect(ui->treeWidget, SIGNAL(customContextMenuRequested(const QPoint&)), SLOT(onCustomContextMenuRequested(const QPoint&)));
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionInfo, SIGNAL(triggered()), this, SLOT(info()));
    connect(ui->actionSave, SIGNAL(triggered()), this, SLOT(save()));
    connect(ui->actionSearch, SIGNAL(triggered()), this, SLOT(search()));
    connect(ui->actionList_View, SIGNAL(triggered()), this, SLOT(switchView()));
    connect(ui->actionMerge, SIGNAL(triggered()), this, SLOT(switchMerge()));
    connect(ui->actionSpecTypes_Overview, SIGNAL(triggered()), this, SLOT(showSpecTypes()));
    connect(ui->navigation, SIGNAL(clicked(const QModelIndex&)),this, SLOT(getSelectedElement(const QModelIndex&)));

    listView = false;
    mergeTextAndChapter = true;
}

MainWindow::~MainWindow(){
    delete ui;
}

/**
 * @brief MainWindow::open routine for opening a reqif file
 */
void MainWindow::open(){
    fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open ReqIF File"), ".",
                                   tr("ReqIf files (*.reqif *.xml)"));
    openXmlFile();
}

void MainWindow::openXmlFile(){
    if (!fileName.isEmpty()){
        QString errorStr;
        int errorLine;
        int errorColumn;
        QDomDocument doc;

        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            QErrorMessage errorMessage;
            errorMessage.showMessage(tr("Error: Cannot read file ") + qPrintable(fileName) +": " + qPrintable(file.errorString()));
            errorMessage.exec();
            return;
        }

        if(parser != NULL){
            parser->clear();
        }

        if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
            qDebug() << errorStr;
            return;
        }

        QDomElement root = doc.documentElement();

        if (root.tagName() == "REQ-IF") {
            parser = new DomParser(ui->treeView, mergeTextAndChapter);
        } else if (root.tagName() == "RIF") {
            parser = new RifParser(ui->treeView, mergeTextAndChapter);
        } else {
            doc.clear();
            file.close();
            return;
        }

        QFileInfo fileInfo(file.fileName());
        QString xmlPath = fileInfo.path();

        parser->parseStructure(doc, xmlPath);
        ReqModel *model = parser->getReqModel();
        ui->navigation->setModel(model);

        int rows = model->rowCount();

        for (int i = 1; i < rows; ++i) {
            ui->navigation->setColumnHidden(i, true);
        }

        setWindowTitle(fileInfo.fileName() +tr(" - ReqIF Reader"));
        doc.clear();
        file.close();
    }
}

/**
 * @brief MainWindow::info this dialog shows more infos about the current reqif file
 */
void MainWindow::info(){
    if(parser != NULL){
        InfoDialog dialog(this, parser->getTitle(), parser->getreqIfSourceTool(), parser->getCreationTime());
        dialog.exec();
    }
}

void MainWindow::save(){
    ReqIfXMLWriter xmlWriter;
    QHash<QString, DataType> dataTypeList = parser->getDataTypes();

    xmlWriter.writeDatatype(dataTypeList);
}

void MainWindow::switchView(){
    listView = !listView;
    if(listView) {
        ui->treeView->expandAll();
    } else {
        ui->treeView->collapseAll();
    }

}

void MainWindow::switchMerge(){
    mergeTextAndChapter = !mergeTextAndChapter;
    openXmlFile();
}

/**
 * @brief MainWindow::search opens search dialog
 */
void MainWindow::search(){
    if (!searchDialog) {
         searchDialog = new SearchDialog(this, ui->treeView);
     }
     searchDialog->show();
     searchDialog->raise();
     searchDialog->activateWindow();
}


void MainWindow::showSpecTypes(){
    if (!specTypeOverview) {
        specTypeOverview = new SpecTypesOverviewDialog(this);
    }
    specTypeOverview->show();
    specTypeOverview->raise();
    specTypeOverview->activateWindow();
    if (parser) {
        specTypeOverview->setSpecTypeList(parser->getSpecTypes());
    }
}

/**
 * @brief MainWindow::about shows infos about this programm
 */
void MainWindow::about(){
    QMessageBox::about(this, tr("About ReqIF Reader"),
            tr("<h2>ReqIF Reader 0.1</h2>"
               "<a href=\"https://github.com/ripper2256/reqifreader\">https://github.com/ripper2256/reqifreader</a>"
               "<p>This program is free software; you can redistribute it and/or modify "
               "it under the terms of the GNU General Public License as published by the Free Software "
               "Foundation; either version 3 of the License, or (at your option) any later version."
               "<p>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; "
               "without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."
               "<p>See the GNU General Public License for more details. "
               "<p> You should have received a copy of the GNU General Public License along with this "
               "program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA."));
}

void MainWindow::getSelectedElement(const QModelIndex &index){
    ui->treeView->setCurrentIndex(index);
}

void MainWindow::onCustomContextMenuRequested(const QPoint& pos) {
    //QTreeWidgetItem* item = ui->treeWidget->itemAt(pos);
    //if (item) {
    // Note: We must map the point to global from the viewport to
    // account for the header.
        //showContextMenu(item, ui->treeWidget->viewport()->mapToGlobal(pos));
    //}
}

void MainWindow::showContextMenu(QTreeWidgetItem* item, const QPoint& globalPos) {
    QMenu menu;
    menu.addAction("This is a type 1");
    menu.exec(globalPos);
}
