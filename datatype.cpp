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
