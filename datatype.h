#ifndef DATATYPE_H
#define DATATYPE_H

#include "reqifbaseelement.h"
#include <QHash>
#include "enumvalue.h"

class DataType : public ReqIfBaseElement
{
public:
    DataType();
    DataType(const QString &reqifID, const QString &name, const QString &base, bool isEnum);
    QString getBaseType();
    void addEnumValue(const QString &reqifID, const EnumValue &enumValue);
    QHash<QString, EnumValue> getEnumValues();
    QList<QString> getEnumValuesAsList();
    bool isEnum();
    void setMin(long long minimum);
    void setMax(long long maximum);
    void setAccuracy(long long accuracy);
    long long getAccuracy();
    long long getMin();
    long long getMax();

private:
    bool enumDatatype;
    QString baseType;
    QHash<QString, EnumValue> enumValuesList;
    long long max;
    long long min;
    long long accuracy;
};

#endif // DATATYPE_H
