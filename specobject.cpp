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

/**
 * @brief SpecObject::SpecObject this constructor should not be used, it is just nesessary for list operations
 */
SpecObject::SpecObject(){
}

/**
 * @brief SpecObject::SpecObject constructor
 * @param reqifID
 */
SpecObject::SpecObject(const QString &reqifID){
    identifier = reqifID;
}

/**
 * @brief SpecObject::getReqifID returns reqifid for this spec-object
 * @return
 */
QString SpecObject::getReqifID(){
    return identifier;
}

/**
 * @brief SpecObject::~SpecObject
 */
SpecObject::~SpecObject(){
    attributeValues.clear();
}

/**
 * @brief SpecObject::addAttributValue adds a attribut value
 * @param attrID reqifid for this attribute
 * @param value actual value
 */
void SpecObject::addAttributValue(const QString &attrID, const QString &value){
    attributeValues.insert(attrID, value);
}

/**
 * @brief SpecObject::getAttributValue gets the attribut value from
 * @param attrID attribute reqifid
 * @return
 */
QString SpecObject::getAttributValue(const QString &attrID){
    return attributeValues.value(attrID);
}

/**
 * @brief SpecObject::mergeTextAndHeading merges text and heading into the text attribut
 * @param txtID
 * @param headingID
 */
void SpecObject::mergeTextAndHeading(const QString &txtID, const QString &headingID){
    QString txt = attributeValues.value(txtID);
    QString heading = attributeValues.value(headingID);
    heading = "<h2>"+heading+"</h2>";
    heading.append(txt);
    attributeValues.insert(txtID, heading);
}


