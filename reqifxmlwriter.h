#ifndef REQIFXMLWRITER_H
#define REQIFXMLWRITER_H

#include <QtXml>
#include <QHash>
#include "datatype.h"

class ReqIfXMLWriter
{
public:

    ReqIfXMLWriter();
    void writeDatatype(const QHash<QString, DataType> &dataTypeList);
};

#endif // REQIFXMLWRITER_H
