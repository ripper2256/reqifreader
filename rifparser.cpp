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
#include "rifparser.h"
#include <QDebug>

const QString RifParser::RIF_CHAPTER_NAME = "Object Heading";
const QString RifParser::RIF_TEXT = "Object Text";

RifParser::RifParser(QTreeView *view, bool mergeTextAndChapter) : Parser(view, mergeTextAndChapter){
}

RifParser::~RifParser(){
    clear();
}

bool RifParser::parseStructure(QDomDocument &document, QString &pathToXmlFile){
    doc = document;
    QDomElement root = doc.documentElement();

    if (root.tagName() != "RIF") {
        return false;
    }
    xmlPath = pathToXmlFile;
    parseRIfXmlFile(root);
    specAttributes.clear();
    enumValues.clear();
    specObjectList.clear();
    doc.clear();
    return true;
}

void RifParser::parseRIfXmlFile(const QDomElement &element){
    QDomNode child = element.firstChild();
    parseCoreContent(child.toElement());
}

void RifParser::parseSpecObjects(const QDomNode &element){
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
void RifParser::replaceXhtmlObjects(const QDomNode &element){
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

void RifParser::parseCoreContent(const QDomNode &element){
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
        if (child.toElement().tagName() == "SPEC-HIERARCHY-ROOTS"){
            //creates a delegate for the treewidget
            HTMLDelegate* delegate = new HTMLDelegate();
            treeView->setItemDelegate(delegate);
            parseSpecifications(child.toElement().firstChildElement("SPEC-HIERARCHY-ROOT"));
            treeView->setModel(model);
            adjustHeaderSection();
        }
        child = child.nextSibling();
    }
}

void RifParser::adjustHeaderSection() {
    //if text and chaptername exist and should be merged
    if(mergeTextAndChapterName && labels.contains(RIF_TEXT) && labels.contains(RIF_CHAPTER_NAME)){
        treeView->header()->hideSection(specAttributes.value(headingAttribut));
    } else {
        headingAttribut.clear();
        textAttribut.clear();
    }

    //doubles size of reqif.text column
    if(!textAttribut.isEmpty()){
        const int oldSize = treeView->header()->sectionSize(specAttributes.value(textAttribut));
        treeView->header()->resizeSection(specAttributes.value(textAttribut), 2*oldSize);
    }
}

void RifParser::parseSpecObject(const QDomNode &element){
    QDomNode child = element.firstChildElement("VALUES").firstChild();
    QString reqifID = element.firstChildElement("IDENTIFIER").text();
    SpecObject specObject(reqifID);

    QString str;
    QTextStream stream(&str);

    while (!child.isNull()) {
        if(child.toElement().hasAttribute("THE-VALUE")){ //parses simple attributs, e.g. real, int, etc.
            specObject.addAttributValue(child.firstChildElement("DEFINITION").firstChild().toElement().text(),child.toElement().attribute("THE-VALUE"));
        }
        if(child.toElement().tagName() == "ATTRIBUTE-VALUE-EMBEDDED-DOCUMENT"){ //parses xhtml attributes
            QDomNode xhtml = child.firstChildElement("XHTML-CONTENT");

            replaceXhtmlObjects(xhtml);
            str.clear();
            xhtml.firstChild().save(stream, 4);
            stream.flush();
            str.replace(QString("rif-xhtml:"), QString(""));
            specObject.addAttributValue(child.firstChildElement("DEFINITION").firstChild().toElement().text(), str);
        }

        if(child.toElement().tagName() == "ATTRIBUTE-VALUE-ENUMERATION"){ //parses enum values
            QDomNode enumValueRef = child.firstChildElement("VALUES").firstChild();
            QString enumAsString = "";
            while (!enumValueRef.isNull()) {
                enumAsString += enumValues.value(enumValueRef.toElement().text());
                enumValueRef = enumValueRef.nextSibling();
                if(!enumValueRef.isNull())
                    enumAsString += "\n";
            }
            specObject.addAttributValue(child.firstChildElement("DEFINITION").firstChild().toElement().text(), enumAsString);
        }

        child = child.nextSibling();
    }
    specObjectList.insert(reqifID, specObject);
}

void RifParser::parseDatatypes(const QDomNode &element){
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.toElement().tagName() == "DATATYPE-DEFINITION-ENUMERATION"){
            QDomNode enumValue = child.firstChildElement("SPECIFIED-VALUES");
            parseEnumValues(enumValue);
        }
        child = child.nextSibling();
    }
}

void RifParser::parseEnumValues(const QDomNode &element){
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.toElement().tagName() == "ENUM-VALUE"){
            QString identifier = child.firstChildElement("IDENTIFIER").text();
            QString longName = child.firstChildElement("LONG-NAME").text();
            enumValues.insert(identifier, longName);
        }
        child = child.nextSibling();
    }
}



void RifParser::parseSpecTypes(const QDomNode &element){
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if(child.toElement().tagName() == "SPEC-TYPE"){

            QDomNode attrDefElement = child.firstChildElement("SPEC-ATTRIBUTES").firstChild();
            while (!attrDefElement.isNull()) {
                QString reqifID = attrDefElement.firstChildElement("IDENTIFIER").text();
                specAttributes.insert(reqifID, specAttributes.size());
                QString longName = attrDefElement.firstChildElement("LONG-NAME").text();
                labels << longName;
                if(longName == RIF_TEXT){ //has reqif.text attribute
                    textAttribut = reqifID;
                }
                if(longName == RIF_CHAPTER_NAME){ //has reqif.chapterName
                    headingAttribut = reqifID;
                }
                SpecType specType(reqifID, longName, attrDefElement.toElement().tagName(), "");
                specTypeList.append(specType);

                attrDefElement = attrDefElement.nextSibling();
            }
        }
        child = child.nextSibling();
    }
    model->setHeaderData(labels);
}


void RifParser::parseSpecifications(const QDomNode &element, TreeItem *parent){
    QDomNode child = element.firstChildElement("CHILDREN").firstChildElement("SPEC-HIERARCHY");
    while (!child.isNull()) {
         QList<QVariant> itemData;

         QString specObjectID = child.firstChildElement("OBJECT").firstChild().toElement().text();
         SpecObject specObject = specObjectList.value(specObjectID);
         if(mergeTextAndChapterName){
            specObject.mergeTextAndHeading(textAttribut, headingAttribut);
         }

         QHash<QString, int>::iterator i;
         //fill list with items
         for (i = specAttributes.begin(); i != specAttributes.end(); ++i){
             itemData << specObject.getAttributValue(i.key());
         }
         //place items at correct position
         for (i = specAttributes.begin(); i != specAttributes.end(); ++i){
             itemData[i.value()] = specObject.getAttributValue(i.key());
         }
         TreeItem *item = model->setupModelData(itemData,parent);

         parseSpecifications(child, item);
         child = child.nextSibling();
     }
}
