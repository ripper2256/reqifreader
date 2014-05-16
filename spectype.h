#ifndef SPECTYPE_H
#define SPECTYPE_H

#include "reqifbaseelement.h"

class SpecType : public ReqIfBaseElement
{
public:
    SpecType(const QString &reqifID, const QString &name, const QString &xmlType, const QString &definition);
    QString getDefinitionRef();
    QString getType();

private:
    QString definitionRef;
    QString type;
};

#endif // SPECTYPE_H
