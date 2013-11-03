#include "searchdialog.h"
#include "ui_searchdialog.h"

#include <QHeaderView>
#include <QDebug>

SearchDialog::SearchDialog(QWidget *parent, QTreeWidget *tree) : QDialog(parent), ui(new Ui::SearchDialog){
    ui->setupUi(this);
    connect(ui->searchButton, SIGNAL(clicked()), this, SLOT(search()));
    connect(ui->nextButton, SIGNAL(clicked()), this, SLOT(next()));
    connect(ui->previousButton, SIGNAL(clicked()), this, SLOT(prev()));
    treeWidget = tree;
    currentPosition = 0;
}

SearchDialog::~SearchDialog(){
    delete ui;
}

void SearchDialog::search(){
    currentPosition = 0;
    searchResults.clear();
    for(int i=0;i<treeWidget->columnCount();i++){
        searchResults.append(treeWidget->findItems(ui->lineEditSearch->text(), Qt::MatchContains | Qt::MatchRecursive, i));
    }
    if(!searchResults.empty())
        treeWidget->setCurrentItem(searchResults.at(currentPosition));
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
    currentPosition = currentPosition - 1 < 0 ? currentPosition-- : currentPosition = 0;
    treeWidget->setCurrentItem(searchResults.at(currentPosition));
}


