#ifndef ENUMVALUE_H
#define ENUMVALUE_H

#include "reqifbaseelement.h"

class EnumValue : public ReqIfBaseElement
{
public:
    EnumValue();
    EnumValue(const QString &reqifID, const QString &name, const QString &keyValue, const QString &otherContentValue);
    QString getKey();
    QString getOtherContent();

private:
    QString key;
    QString otherContent;
};

#endif // ENUMVALUE_H
