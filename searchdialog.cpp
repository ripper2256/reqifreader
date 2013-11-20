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

SearchDialog::SearchDialog(QWidget *parent, QTreeWidget *tree) : QDialog(parent), ui(new Ui::SearchDialog){
    ui->setupUi(this);
    ui->lineEditSearch->setFocus();
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(search()));
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(ui->previousButton, SIGNAL(clicked()), this, SLOT(prev()));
    treeWidget = tree;
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

void SearchDialog::setEnableButtons(bool enabled){
    ui->nextButton->setEnabled(enabled);
    ui->previousButton->setEnabled(enabled);
}

void SearchDialog::search(){
    reset();
    if(ui->lineEditSearch->text().isEmpty()){
        return;
    }

    for(int i=0;i<treeWidget->columnCount();i++){
        Qt::MatchFlags options = Qt::MatchContains | Qt::MatchRecursive;
        if(ui->caseCheckBox->isChecked())
            options = options | Qt::MatchCaseSensitive;

        if(ui->regExpCheckBox->isChecked())
            options = options | Qt::MatchRegExp;

        searchResults.append(treeWidget->findItems(ui->lineEditSearch->text(), options, i));
    }
    if(!searchResults.empty())
        treeWidget->setCurrentItem(searchResults.at(currentPosition));
    setEnableButtons(!searchResults.empty());
}

void SearchDialog::next(){
    if(searchResults.empty())
        return;
    currentPosition = currentPosition + 1 % searchResults.size();
    treeWidget->setCurrentItem(searchResults.at(currentPosition));
}

void SearchDialog::prev(){
    if(searchResults.empty())
        return;
    currentPosition = currentPosition - 1 < 0 ? 0 : currentPosition - 1;
    treeWidget->setCurrentItem(searchResults.at(currentPosition));
}


