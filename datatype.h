#ifndef DATATYPE_H
#define DATATYPE_H

#include "reqifbaseelement.h"

class DataType : public ReqIfBaseElement
{
public:
    DataType(const QString &reqifID, const QString &name, const QString &base);
    QString getBaseType();
    bool isEnum();

private:
    bool enumDatatype;
    QString baseType;
    long long max;
    long long min;
};

#endif // DATATYPE_H
