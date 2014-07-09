#include "reqifxmlwriter.h"

ReqIfXMLWriter::ReqIfXMLWriter()
{
}

void ReqIfXMLWriter::writeDatatype(const QHash<QString, DataType> &dataTypeList){
    QList<DataType> dataTypes = dataTypeList.values();

    QDomDocument doc("REQ-IF");
    QDomElement root = doc.createElement("REQ-IF");
    doc.appendChild(root);

    QDomElement core = doc.createElement("CORE-CONTENT");
    root.appendChild(core);

    QDomElement dataTypesElement = doc.createElement("DATATYPES");
    core.appendChild(dataTypesElement);

    foreach (DataType type, dataTypes) {
        QDomElement tag = doc.createElement(type.getBaseType());
        tag.setAttribute("IDENTIFIER",type.getIdentifier());
        tag.setAttribute("LONG-NAME", type.getLongName());
        dataTypesElement.appendChild(tag);
    }

    /*QDomElement tag = doc.createElement("Greeting");
    root.appendChild(tag);

    QDomText t = doc.createTextNode("Hello World");
    tag.appendChild(t);*/

    QString xml = doc.toString();
    qDebug() << xml;
}
