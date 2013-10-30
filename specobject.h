#ifndef SPECOBJECT_H
#define SPECOBJECT_H

#include <QString>
#include <QHash>

class SpecObject
{
public:
    SpecObject();
    SpecObject(const QString &reqifID);
    ~SpecObject();
    QString getReqifID();
    void addAttributValue(const QString &attrID, const QString &value);
    QString getAttributValue(const QString &attrID);

private:
    QString identifier;
    QHash<QString, QString> attributeValues;
};

#endif // SPECOBJECT_H
