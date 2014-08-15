/*
 * This file is part of the ReqIf Reader.
 *
 *  ReqIf Reader is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  ReqIf Reader is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with ReqIf Reader.  If not, see <http://www.gnu.org/licenses/>.
*/

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
