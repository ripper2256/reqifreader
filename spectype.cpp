#include "spectype.h"

SpecType::SpecType(const QString &reqifID, const QString &name, const QString &xmlType, const QString &definition): ReqIfBaseElement(reqifID, name){
    definitionRef = definition;
    type = xmlType;
}

QString SpecType::getDefinitionRef(){
    return definitionRef;
}

QString SpecType::getType(){
    return type;
}
