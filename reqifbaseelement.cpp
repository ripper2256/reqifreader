#include "reqifbaseelement.h"

ReqIfBaseElement::ReqIfBaseElement(){

}

ReqIfBaseElement::ReqIfBaseElement(const QString &reqifID, const QString &name){
    identifier = reqifID;
    longName = name;
}

QString ReqIfBaseElement::getIdentifier(){
    return identifier;
}

QString ReqIfBaseElement::getLongName(){
    return longName;
}
