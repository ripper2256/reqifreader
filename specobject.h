#ifndef SPECOBJECT_H
#define SPECOBJECT_H

#include <QString>
#include <QHash>
#include <QVariant>

class SpecObject
{
public:
    SpecObject();
    SpecObject(const QString &reqifID);
    ~SpecObject();
    QString getReqifID();
    void addAttributValue(const QString &attrID, const QString &value);
    void addAttributValue2(const QString &attrID, const QVariant &value);
    QString getAttributValue(const QString &attrID);
    QVariant getAttributValue2(const QString &attrID);
    void mergeTextAndHeading(const QString &txtID, const QString &headingID);

private:
    QString identifier;
    QHash<QString, QString> attributeValuesString;
    QHash<QString, QVariant> attributeValues;
};

#endif // SPECOBJECT_H
