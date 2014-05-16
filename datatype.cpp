#include "datatype.h"

DataType::DataType(const QString &reqifID, const QString &name, const QString &base, bool isEnum) : ReqIfBaseElement(reqifID, name){
    baseType = base;
    enumDatatype = isEnum;
}

DataType::getBaseType() {
    return baseType;
}

DataType::isEnum(){
    return enumDatatype;
}
