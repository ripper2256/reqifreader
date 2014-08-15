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
