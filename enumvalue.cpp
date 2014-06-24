#include "enumvalue.h"

EnumValue::EnumValue(){

}

EnumValue::EnumValue(const QString &reqifID, const QString &name, const QString &keyValue, const QString &otherContentValue) : ReqIfBaseElement(reqifID, name){
    key = keyValue;
    otherContent = otherContentValue;
}

QString EnumValue::getKey(){
    return key;
}

QString EnumValue::getOtherContent(){
    return otherContent;
}

