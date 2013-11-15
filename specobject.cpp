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

#include "specobject.h"
#include <QDebug>
SpecObject::SpecObject(){
}

SpecObject::SpecObject(const QString &reqifID){
    identifier = reqifID;
}

QString SpecObject::getReqifID(){
    return identifier;
}

SpecObject::~SpecObject(){
    attributeValues.clear();
}

void SpecObject::addAttributValue(const QString &attrID, const QString &value){
    attributeValues.insert(attrID, value);
}

QString SpecObject::getAttributValue(const QString &attrID){
    return attributeValues.value(attrID);
}

void SpecObject::mergeTextAndHeading(const QString &txtID, const QString &headingID){
    QString txt = attributeValues.value(txtID);
    QString heading = attributeValues.value(headingID);
    heading = "<h2>"+heading+"</h2>";
    heading.append(txt);
    attributeValues.insert(txtID, heading);
}


