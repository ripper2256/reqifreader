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
#include "searchdialog.h"
#include "ui_searchdialog.h"

#include <QHeaderView>
#include <QDebug>

SearchDialog::SearchDialog(QWidget *parent, QTreeView *tree) : QDialog(parent), ui(new Ui::SearchDialog){
    ui->setupUi(this);
    ui->lineEditSearch->setFocus();
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(search()));
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(ui->previousButton, SIGNAL(clicked()), this, SLOT(prev()));
    treeView = tree;
    currentPosition = 0;
    setEnableButtons(false);
}

SearchDialog::~SearchDialog(){
    reset();
    delete ui;
}

void SearchDialog::reset(){
    currentPosition = 0;
    searchResults.clear();
    setEnableButtons(false);
}

/**
 * @brief SearchDialog::setEnableButtons enables or disables the next and previous button
 * @param enabled
 */
void SearchDialog::setEnableButtons(bool enabled){
    ui->nextButton->setEnabled(enabled);
    ui->previousButton->setEnabled(enabled);
}

/**
 * @brief SearchDialog::search serach routine
 */
void SearchDialog::search(){
    reset();
    if(ui->lineEditSearch->text().isEmpty()){
        return;
    }

    for(int i=0;i<treeView->model()->columnCount();i++){
        Qt::MatchFlags options = Qt::MatchContains | Qt::MatchRecursive;
        if(ui->caseCheckBox->isChecked())
            options = options | Qt::MatchCaseSensitive;

        if(ui->regExpCheckBox->isChecked())
            options = options | Qt::MatchRegExp;
        //treeView->findChild()
        //searchResults.append(treeWidget->findItems(ui->lineEditSearch->text(), options, i));
    }
    if(!searchResults.empty())
        treeView->setCurrentIndex(searchResults.at(currentPosition));
    setEnableButtons(!searchResults.empty());
}

/**
 * @brief SearchDialog::next hops to netx search result
 */
void SearchDialog::next(){
    if(searchResults.empty())
        return;
    currentPosition = currentPosition + 1 % searchResults.size();
    treeView->setCurrentIndex(searchResults.at(currentPosition));
}

/**
 * @brief SearchDialog::prev hops to previous search result
 */
void SearchDialog::prev(){
    if(searchResults.empty())
        return;
    currentPosition = currentPosition - 1 < 0 ? 0 : currentPosition - 1;
    treeView->setCurrentIndex(searchResults.at(currentPosition));
}


