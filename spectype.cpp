#include "spectype.h"

SpecType::SpecType(const QString &reqifID, const QString &name, const QString &xmlType, const QString &definition){
    identifier = reqifID;
    longName = name;
    definitionRef = definition;
    type = xmlType;
}

QString SpecType::getIdentifier(){
    return identifier;
}

QString SpecType::getLongName(){
    return longName;
}

QString SpecType::getDefinitionRef(){
    return definitionRef;
}

QString SpecType::getType(){
    return type;
}
