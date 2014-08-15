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

#include <QTreeWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include <QString>
#include "domparser.h"
#include "htmldelegate.h"
#include "intdelegate.h"
#include "spectype.h"
#include "treeitem.h"
#include "enumdelegate.h"
#include "datedelegate.h"
#include "booldelegate.h"

const QString DomParser::REQIF_CHAPTER_NAME = "ReqIF.ChapterName";
const QString DomParser::REQIF_TEXT = "ReqIF.Text";

const QString DomParser::REQIF_HTML_TYPE = "ATTRIBUTE-DEFINITION-XHTML";
const QString DomParser::REQIF_ENUM_TYPE = "ATTRIBUTE-DEFINITION-ENUMERATION";
const QString DomParser::REQIF_STRING_TYPE = "ATTRIBUTE-DEFINITION-STRING";
const QString DomParser::REQIF_INT_TYPE = "ATTRIBUTE-DEFINITION-INTEGER";
const QString DomParser::REQIF_REAL_TYPE = "ATTRIBUTE-DEFINITION-REAL";
const QString DomParser::REQIF_DATE_TYPE = "ATTRIBUTE-DEFINITION-DATE";
const QString DomParser::REQIF_BOOL_TYPE = "ATTRIBUTE-DEFINITION-BOOLEAN";

DomParser::DomParser(QTreeView *view, bool mergeTextAndChapter) : Parser(view, mergeTextAndChapter){
}

DomParser::~DomParser(){
    textAttribut.clear();
    headingAttribut.clear();
    clear();
}


bool DomParser::parseStructure(QDomDocument &document, QString &pathToXmlFile){
    doc = document;
    QDomElement root = doc.documentElement();

    if (root.tagName() != "REQ-IF") {
        return false;
    }
    xmlPath = pathToXmlFile;
    treeView->header()->reset();
    parseReqIfXmlFile(root);
    specAttributes.clear();
    enumValues.clear();
    specObjectList.clear();
    doc.clear();
    return true;
}

/**
 * @brief DomParser::parseReqIfXmlFile entry method for parsing a reqif QDomElement structure
 * @param element
 */
void DomParser::parseReqIfXmlFile(const QDomElement &element){
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.toElement().tagName() == "THE-HEADER"){
            parseHeader(child.firstChild());
        }
        if (child.toElement().tagName() == "CORE-CONTENT"){
            parseCoreContent(child.toElement().firstChild().firstChild());
        }
        child = child.nextSibling();
    }

}

/**
 * @brief DomParser::parseHeader parses the header section, of a reqif file
 * @param element
 */
void DomParser::parseHeader(const QDomNode &element){
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.toElement().tagName() == "CREATION-TIME") {
            creationTime = child.toElement().text();
        } else if (child.toElement().tagName() == "REQ-IF-TOOL-ID") {
            reqIfTool = child.toElement().text();
        } else if (child.toElement().tagName() == "REQ-IF-VERSION") {
            reqifVersion = child.toElement().text();
        } else if (child.toElement().tagName() == "SOURCE-TOOL-ID") {
            reqifSourceTool = child.toElement().text();
        } else if (child.toElement().tagName() == "TITLE") {
            title = child.toElement().text();
        }

        child = child.nextSibling();
    }
}

/**
 * @brief DomParser::parseCoreContent parses the CORE-CONTENT of a reqif file
 * @param element
 */
void DomParser::parseCoreContent(const QDomNode &element){
    QDomNode child = element;
    while (!child.isNull()) {
        if (child.toElement().tagName() == "SPEC-TYPES"){
            parseSpecTypes(child.toElement());
        }
        if (child.toElement().tagName() == "SPEC-OBJECTS"){
            parseSpecObjects(child.toElement());
        }
        if (child.toElement().tagName() == "DATATYPES"){
            parseDatatypes(child.toElement());
        }
        if (child.toElement().tagName() == "SPECIFICATIONS"){
            parseSpecifications(child.toElement().firstChild());
            treeView->setModel(model);
            adjustHeaderSection();
            setDelegates();
        }
        child = child.nextSibling();
    }
}


void DomParser::setDelegates(){
    //creates delegates
    foreach (SpecType spType, specTypeList) {
        int headerPosition = specAttributes.value(spType.getIdentifier());
        if (spType.getType() == REQIF_HTML_TYPE) {
            HTMLDelegate* delegate = new HTMLDelegate();
            treeView->setItemDelegateForColumn(headerPosition, delegate);
        } else if (spType.getType() == REQIF_INT_TYPE) {
            IntDelegate* delegate = new IntDelegate();
            treeView->setItemDelegateForColumn(headerPosition, delegate);
        } else if (spType.getType() == REQIF_ENUM_TYPE) {
            QStringList list(spType.getDefinitionRef().getEnumValuesAsList());
            EnumDelegate *delegate = new EnumDelegate(list);
            treeView->setItemDelegateForColumn(headerPosition, delegate);
        } else if (spType.getType() == REQIF_REAL_TYPE) {

        } else if(spType.getType() == REQIF_STRING_TYPE) {

        } else if(spType.getType() == REQIF_DATE_TYPE) {
            DateDelegate* delegate = new DateDelegate();
            treeView->setItemDelegateForColumn(headerPosition, delegate);
        } else if(spType.getType() == REQIF_BOOL_TYPE) {
            BoolDelegate *delegate = new BoolDelegate();
            treeView->setItemDelegateForColumn(headerPosition, delegate);
        }
    }
}

void DomParser::adjustHeaderSection(){
    //doubles size of reqif.text column
    if(!textAttribut.isEmpty()){
        const int oldSize = treeView->header()->sectionSize(specAttributes.value(textAttribut));
        treeView->header()->resizeSection(specAttributes.value(textAttribut), 4*oldSize);
    }

    //if text and chaptername exist and should be merged
    if(mergeTextAndChapterName && labels.contains(REQIF_TEXT) && labels.contains(REQIF_CHAPTER_NAME)){
        //treeView->header()->hideSection(specAttributes.value(headingAttribut));
    } else {
        headingAttribut.clear();
        textAttribut.clear();
    }

}

/**
 * @brief DomParser::parseSpecifications
 * @param element
 * @param parent
 */
void DomParser::parseSpecifications(const QDomNode &element, TreeItem *parent){
    QDomNode child = element.firstChildElement("CHILDREN").firstChild();
    while (!child.isNull()) {
        bool tableInternal = false;
        QVector<QVariant> itemData(specAttributes.size());
        QVector<QString> ref(specAttributes.size());

        QString specObjectID = child.firstChildElement("OBJECT").firstChild().toElement().text();
        SpecObject specObject = specObjectList.value(specObjectID);

        if(mergeTextAndChapterName){
            specObject.mergeTextAndHeading(textAttribut, headingAttribut);
        }

        QHash<QString, int>::iterator i;
        for (i = specAttributes.begin(); i != specAttributes.end(); ++i){
            itemData[i.value()] = specObject.getAttributValue2(i.key());
            ref[i.value()] = i.key();
        }

        QList<QVariant> itemList;
        QList<QString> refList;
        itemList = itemList.fromVector(itemData);
        refList = refList.fromVector(ref);

        TreeItem *item = model->setupModelData(specObjectID, itemList, refList, parent);

        //stop parsing child nodes, if it is an internal table (e.g. doors table)
        if(child.toElement().hasAttribute("IS-TABLE-INTERNAL")){
            if(child.toElement().attribute("IS-TABLE-INTERNAL") == "true")
                tableInternal = true;
        }

        if(!tableInternal)
            parseSpecifications(child, item);
        child = child.nextSibling();
    }
}

/**
 * @brief DomParser::parseDatatypes parses all posible enum values
 * @param element
 */
void DomParser::parseDatatypes(const QDomNode &element){
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.toElement().tagName() == "DATATYPE-DEFINITION-ENUMERATION"){
            DataType datatype(child.toElement().attribute("IDENTIFIER"),child.toElement().attribute("LONG-NAME"), child.toElement().tagName(), true);
            parseEnumValues(child.firstChild(), &datatype);
            dataTypeList.insert(datatype.getIdentifier(), datatype);
        } else {
            DataType datatype(child.toElement().attribute("IDENTIFIER"),child.toElement().attribute("LONG-NAME"), child.toElement().tagName(), false);
            if(child.toElement().hasAttribute("MAX")) {
                datatype.setMax(child.toElement().attribute("MAX").toLongLong());
            }
            if(child.toElement().hasAttribute("MIN")) {
                datatype.setMin(child.toElement().attribute("MIN").toLongLong());
            }
            if(child.toElement().hasAttribute("ACCURACY")) {
                datatype.setAccuracy(child.toElement().attribute("MIN").toLongLong());
            }
            dataTypeList.insert(datatype.getIdentifier(), datatype);
        }

        child = child.nextSibling();
    }
}

void DomParser::parseEnumValues(const QDomNode & element, DataType *dataType) {
    QDomNode child = element.firstChildElement("ENUM-VALUE");
    while (!child.isNull()) {
        QString longName = child.toElement().attribute("LONG-NAME");
        QString reqifID = child.toElement().attribute("IDENTIFIER");
        QString key = child.firstChild().firstChild().toElement().attribute("KEY");
        QString otherContent = child.firstChild().firstChild().toElement().attribute("OTHER-CONTENT");
        EnumValue enumValue(reqifID, longName, key, otherContent);
        dataType->addEnumValue(reqifID, enumValue);
        enumValuesList.insert(reqifID, enumValue);
        child = child.nextSibling();
    }
}

void DomParser::parseSpecTypes(const QDomNode &element){
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if(child.toElement().tagName() == "SPEC-OBJECT-TYPE"){
            QDomNode attrDefElement = child.firstChild().firstChild();
            while (!attrDefElement.isNull()) {
                QString reqifID = attrDefElement.toElement().attribute("IDENTIFIER");
                QString longName = attrDefElement.toElement().attribute("LONG-NAME");

                QString multiValuedString = attrDefElement.toElement().attribute("MULTI-VALUED");
                bool multiValued = false;
                if(!multiValuedString .isEmpty()){
                    if(QString::compare(multiValuedString,"true",Qt::CaseInsensitive) == 0){
                        multiValued = true;
                    }
                }
                //get datatype reference
                QString typeRef = attrDefElement.firstChildElement("TYPE").firstChild().toElement().text();

                if(longName == REQIF_TEXT){ //has reqif.text attribute
                    textAttribut = reqifID;
                }
                if(longName == REQIF_CHAPTER_NAME){ //has reqif.chapterName
                    headingAttribut = reqifID;
                }

                SpecType specType(reqifID, longName, attrDefElement.toElement().tagName(), dataTypeList.value(typeRef), multiValued);
                specTypeList.append(specType);

                attrDefElement = attrDefElement.nextSibling();
            }
        } else if(child.toElement().tagName() == "SPECIFICATION-TYPE"){
            QString reqifID = child.toElement().attribute("IDENTIFIER");
            QString longName = child.toElement().attribute("LONG-NAME");
            ReqIfBaseElement specType(reqifID, longName);
            specificationTypeList.append(specType);
        }
        child = child.nextSibling();
    }

    int position = -1;
    QStringList reqIfFields;
    reqIfFields << "ReqIF.ChapterName";
    reqIfFields << "ReqIF.ForeignID";
    reqIfFields << "ReqIF.Name";
    reqIfFields << "ReqIF.Text";

    foreach (const QString &str, reqIfFields) {
        position = sortCritieria(str);
        if(position != -1) {
            break;
        }
    }

    sortSpecTypes(position);

    model->setHeaderData(labels);

}



void DomParser::parseSpecObjects(const QDomNode &element){
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        parseSpecObject(child.toElement());
        child = child.nextSibling();
    }

}

/**
 * @brief DomParser::replaceXhtmlObjects replace object tag with image tag
 * @param element
 */
void DomParser::replaceXhtmlObjects(const QDomNode &element){
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if(child.toElement().tagName() == "xhtml:object"){
            QDomElement imageElement = doc.createElement(QString("img"));
            if(!child.hasChildNodes()){
                imageElement.setAttribute(QString("src"), xmlPath + QDir::separator() + child.toElement().attribute("data"));
            } else { //select alternative object (should be an image)
                imageElement.setAttribute(QString("src"), xmlPath + QDir::separator() + child.firstChild().toElement().attribute("data"));
            }

            element.toElement().replaceChild(imageElement, child);
        }
        if(child.hasChildNodes()){
            replaceXhtmlObjects(child);
        }

        child = child.nextSibling();
    }
}

/**
 * @brief DomParser::parseSpecObject parse an individual specobject
 * @param element
 */
void DomParser::parseSpecObject(const QDomNode &element){
    QDomNode child = element.firstChildElement("VALUES").firstChild();
    QString reqifID = element.toElement().attribute("IDENTIFIER");
    SpecObject specObject(reqifID);

    QString str;
    QTextStream stream(&str);
    while (!child.isNull()) {
        if(child.toElement().hasAttribute("THE-VALUE")){ //parses simple attributs, e.g. real, int, etc. 
            QString theValue = child.toElement().attribute("THE-VALUE");
            if(child.toElement().tagName() == "ATTRIBUTE-VALUE-BOOLEAN") {
                bool value = QString::compare(theValue, "true",Qt::CaseInsensitive) == 0 ? true : false;
                specObject.addAttributValue2(child.firstChildElement("DEFINITION").firstChild().toElement().text(), value);
            } else if(child.toElement().tagName() == "ATTRIBUTE-VALUE-DATE") {
                QDate value = QDate::fromString(theValue, Qt::ISODate);
                specObject.addAttributValue2(child.firstChildElement("DEFINITION").firstChild().toElement().text(),value);
            } else if(child.toElement().tagName() == "ATTRIBUTE-VALUE-INTEGER") {
                int value = theValue.toInt();
                specObject.addAttributValue2(child.firstChildElement("DEFINITION").firstChild().toElement().text(),value);
            } else {
                specObject.addAttributValue2(child.firstChildElement("DEFINITION").firstChild().toElement().text(),theValue);
            }
        }
        if(child.toElement().tagName() == "ATTRIBUTE-VALUE-XHTML"){ //parses xhtml attributes
            QDomNode xhtml = child.firstChildElement("THE-VALUE");

            replaceXhtmlObjects(xhtml);
            str.clear();
            xhtml.firstChild().save(stream, 4);
            stream.flush();
            str.replace(QString("xhtml:"), QString(""));

            specObject.addAttributValue2(child.firstChildElement("DEFINITION").firstChild().toElement().text(), str);
        }

        if(child.toElement().tagName() == "ATTRIBUTE-VALUE-ENUMERATION"){ //parses enum values
            QDomNode enumValueRef = child.firstChild().firstChild();
            QString enumReqifID = child.firstChildElement("DEFINITION").firstChild().toElement().text();
            QStringList strList;
            while (!enumValueRef.isNull()) {
                EnumValue enumValue = enumValuesList.value(enumValueRef.toElement().text());
                strList.append(enumValue.getLongName());
                enumValueRef = enumValueRef.nextSibling();
            }
            specObject.addAttributValue2(enumReqifID, strList);
            //specObject.addAttributValue2(enumReqifID, enumAsString);
        }

        child = child.nextSibling();
    }
    specObjectList.insert(reqifID, specObject);
}


