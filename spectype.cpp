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
