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

#include "reqifxmlwriter.h"

ReqIfXMLWriter::ReqIfXMLWriter()
{
}

void ReqIfXMLWriter::writeDatatype(const QHash<QString, DataType> &dataTypeList){
    QList<DataType> dataTypes = dataTypeList.values();

    QDomDocument doc("REQ-IF");
    QDomElement root = doc.createElement("REQ-IF");
    doc.appendChild(root);

    QDomElement core = doc.createElement("CORE-CONTENT");
    root.appendChild(core);

    QDomElement dataTypesElement = doc.createElement("DATATYPES");
    core.appendChild(dataTypesElement);

    foreach (DataType type, dataTypes) {
        QDomElement tag = doc.createElement(type.getBaseType());
        tag.setAttribute("IDENTIFIER",type.getIdentifier());
        tag.setAttribute("LONG-NAME", type.getLongName());
        dataTypesElement.appendChild(tag);
    }

    /*QDomElement tag = doc.createElement("Greeting");
    root.appendChild(tag);

    QDomText t = doc.createTextNode("Hello World");
    tag.appendChild(t);*/

    QString xml = doc.toString();
    qDebug() << xml;
}
