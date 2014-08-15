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

#include "spectype.h"

SpecType::SpecType(const QString &reqifID, const QString &name, const QString &xmlType, const DataType &definition, bool multiValue): ReqIfBaseElement(reqifID, name){
    definitionRef = definition;
    type = xmlType;
    multiValued = multiValue;
}

DataType SpecType::getDefinitionRef(){
    return definitionRef;
}

QString SpecType::getType(){
    return type;
}

bool SpecType::getMultiValued(){
    return multiValued;
}
