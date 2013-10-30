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

#include "infodialog.h"
#include "ui_infodialog.h"

InfoDialog::InfoDialog(QWidget *parent, const QString &title, const QString &sourceTool, const QString &creaTime) : QDialog(parent),
    ui(new Ui::InfoDialog){

    ui->setupUi(this);
    ui->lETitle->setText(title);
    ui->lESToolID->setText(sourceTool);
    ui->lECreaTime->setText(creaTime);
    connect(ui->closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

InfoDialog::~InfoDialog()
{
    delete ui;
}
