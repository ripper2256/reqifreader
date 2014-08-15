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

#ifndef REQIFXMLWRITER_H
#define REQIFXMLWRITER_H

#include <QtXml>
#include <QHash>
#include "datatype.h"

class ReqIfXMLWriter
{
public:

    ReqIfXMLWriter();
    void writeDatatype(const QHash<QString, DataType> &dataTypeList);
};

#endif // REQIFXMLWRITER_H
