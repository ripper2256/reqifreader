#ifndef REQIFBASEELEMENT_H
#define REQIFBASEELEMENT_H

#include <QString>

class ReqIfBaseElement
{
public:
    ReqIfBaseElement(const QString &reqifID, const QString &name);
    QString getIdentifier();
    QString getLongName();

private:
    QString identifier;
    QString longName;
};

#endif // REQIFBASEELEMENT_H
