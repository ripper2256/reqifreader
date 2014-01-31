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
#include "spectypesoverviewdialog.h"
#include "ui_spectypesoverviewdialog.h"
#include <QDebug>

SpecTypesOverviewDialog::SpecTypesOverviewDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SpecTypesOverviewDialog){    
    ui->setupUi(this);
}

SpecTypesOverviewDialog::~SpecTypesOverviewDialog(){
    delete ui;
}

void SpecTypesOverviewDialog::setSpecTypeList(QList<SpecType> stList){
    int i=0;
    ui->tableSpecTypes->hide();
    ui->tableSpecTypes->setRowCount(stList.size());
    foreach (SpecType spType, stList) {
        QTableWidgetItem *newItem = new QTableWidgetItem(spType.getIdentifier());
        ui->tableSpecTypes->setItem(i,0,newItem);
        QTableWidgetItem *newItem1 = new QTableWidgetItem(spType.getLongName());
        ui->tableSpecTypes->setItem(i,1,newItem1);
        QTableWidgetItem *newItem2 = new QTableWidgetItem(spType.getType());
        ui->tableSpecTypes->setItem(i,2,newItem2);
        i++;
    }
    ui->tableSpecTypes->show();
}
