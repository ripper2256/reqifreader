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

#include "datatype.h"

DataType::DataType(){

}

DataType::DataType(const QString &reqifID, const QString &name, const QString &base, bool isEnum) : ReqIfBaseElement(reqifID, name){
    baseType = base;
    enumDatatype = isEnum;
}

QString DataType::getBaseType() {
    return baseType;
}

bool DataType::isEnum(){
    return enumDatatype;
}

void DataType::setMax(long long maximum) {
    max = maximum;
}

void DataType::setMin(long long minimum) {
    min = minimum;
}

void DataType::setAccuracy(long long accuracy){
    this->accuracy = accuracy;
}

long long DataType::getAccuracy() {
    return accuracy;
}

long long DataType::getMax() {
    return max;
}

long long DataType::getMin() {
    return min;
}

void DataType::addEnumValue(const QString &reqifID, const EnumValue &enumValue){
    if(isEnum()){
        enumValuesList.insert(reqifID, enumValue);
    }
}

QHash<QString, EnumValue> DataType::getEnumValues(){
    return enumValuesList;
}

QList<QString> DataType::getEnumValuesAsList(){
    QList<QString> resultList;
    QList<EnumValue> enumValues = enumValuesList.values();
    foreach (EnumValue ev, enumValues) {
        resultList.append(ev.getLongName());
    }
    return resultList;
}
