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
#include "searchdialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    connect(ui->actionExit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(about()));
    connect(ui->actionOpen, SIGNAL(triggered()), this, SLOT(open()));
    connect(ui->actionInfo, SIGNAL(triggered()), this, SLOT(info()));
    connect(ui->actionSearch, SIGNAL(triggered()), this, SLOT(search()));
}

MainWindow::~MainWindow(){
    delete ui;
}
void MainWindow::open(){
    QString fileName = QFileDialog::getOpenFileName(this,
                                   tr("Open ReqIF File"), ".",
                                   tr("ReqIf files (*.reqif *.xml)"));
    if (!fileName.isEmpty()){
        QFile file(fileName);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            /*std::cerr << "Error: Cannot read file " << qPrintable(fileName)
                      << ": " << qPrintable(file.errorString())
                      << std::endl;*/
        }

        if(parser != NULL){
            parser->clear();
        }

        parser = new DomParser(ui->treeWidget);
        parser->readFile(file);
        QFileInfo fileInfo(file.fileName());
        setWindowTitle(fileInfo.fileName() +tr(" - ReqIF Reader"));

    }
}


void MainWindow::info(){
    if(parser != NULL){
        InfoDialog dialog(this, parser->getTitle(), parser->getreqIfSourceTool(), parser->getCreationTime());
        dialog.exec();
    }
}

void MainWindow::search(){
    SearchDialog dialog(this, ui->treeWidget);
    dialog.exec();

}

void MainWindow::about(){
    QMessageBox::about(this, tr("About ReqIF Reader"),
            tr("<h2>ReqIF Reader 0.1</h2>"
               "<p>This program is free software; you can redistribute it and/or modify "
               "it under the terms of the GNU General Public License as published by the Free Software "
               "Foundation; either version 3 of the License, or (at your option) any later version."
               "<p>This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; "
               "without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE."
               "<p>See the GNU General Public License for more details. "
               "<p> You should have received a copy of the GNU General Public License along with this "
               "program; if not, write to the Free Software Foundation, Inc., 675 Mass Ave, Cambridge, MA 02139, USA."));
}
