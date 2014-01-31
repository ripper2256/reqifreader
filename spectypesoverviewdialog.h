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
#ifndef SPECTYPESOVERVIEWDIALOG_H
#define SPECTYPESOVERVIEWDIALOG_H

#include <QDialog>
#include "spectype.h"

namespace Ui {
class SpecTypesOverviewDialog;
}

class SpecTypesOverviewDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SpecTypesOverviewDialog(QWidget *parent = 0);
    ~SpecTypesOverviewDialog();
    void setSpecTypeList(QList<SpecType> stList);

private:
    Ui::SpecTypesOverviewDialog *ui;
};

#endif // SPECTYPESOVERVIEWDIALOG_H
