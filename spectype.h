#ifndef SPECTYPE_H
#define SPECTYPE_H

#include "reqifbaseelement.h"
#include "datatype.h"

class SpecType : public ReqIfBaseElement
{
public:
    SpecType(const QString &reqifID, const QString &name, const QString &xmlType, const DataType &definition, bool multiValue);
    DataType getDefinitionRef();
    QString getType();
    bool getMultiValued();

private:
    DataType definitionRef;
    QString type;
    bool multiValued;
};

#endif // SPECTYPE_H
