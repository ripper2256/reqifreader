#ifndef SPECTYPE_H
#define SPECTYPE_H

#include <QString>

class SpecType
{
public:
    SpecType(const QString &reqifID, const QString &name, const QString &xmlType, const QString &definition);
    QString getIdentifier();
    QString getLongName();
    QString getDefinitionRef();
    QString getType();

private:
    QString identifier;
    QString longName;
    QString definitionRef;
    QString type;
};

#endif // SPECTYPE_H
