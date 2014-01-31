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
#include "domparser.h"
#include "htmldelegate.h"
#include "spectype.h"

const QString DomParser::REQIF_CHAPTER_NAME = "ReqIF.ChapterName";
const QString DomParser::REQIF_TEXT = "ReqIF.Text";

DomParser::DomParser(QTreeWidget *tree, bool viewAsList, bool mergeTextAndChapter){
    treeWidget = tree;
    listView = viewAsList;
    mergeTextAndChapterName = mergeTextAndChapter;
}

DomParser::~DomParser(){
    clear();
}

void DomParser::clear(){
    treeWidget->clear();
    treeWidget->setColumnCount(0);
    specAttributes.clear();
    enumValues.clear();
    specObjectList.clear();
    specTypeList.clear();
    doc.clear();
}

/**
 * @brief DomParser::readFile wrapping method for parsing a reqif xml file
 * @param file
 * @return
 */
bool DomParser::readFile(QFile &file){
    QString errorStr;
    int errorLine;
    int errorColumn;


    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
        return false;
    }

    QDomElement root = doc.documentElement();

    if (root.tagName() != "REQ-IF") {
        return false;
    }
    QFileInfo fileInfo(file.fileName());
    xmlPath = fileInfo.path();
    parseReqIfXmlFile(root);
    specAttributes.clear();
    enumValues.clear();
    specObjectList.clear();
    file.close();
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
            //QTime myTimer;
            //myTimer.start();
            parseSpecObjects(child.toElement());
            /*int nMilliseconds = myTimer.elapsed();
            qDebug() << "SPEC-OBJECTS";
            qDebug() << nMilliseconds;*/
        }
        if (child.toElement().tagName() == "DATATYPES"){
            parseDatatypes(child.toElement());
        }
        if (child.toElement().tagName() == "SPECIFICATIONS"){
            treeWidget->hide();
            //creates a delegate for the treewidget
            HTMLDelegate* delegate = new HTMLDelegate();
            treeWidget->setItemDelegate(delegate);
            treeWidget->header()->setSectionsMovable(true);
            parseSpecifications(child.toElement().firstChild(), treeWidget->invisibleRootItem());
            treeWidget->show();
        }
        child = child.nextSibling();
    }
}

/**
 * @brief DomParser::parseSpecifications
 * @param element
 * @param parent
 */
void DomParser::parseSpecifications(const QDomNode &element, QTreeWidgetItem *parent){
    QDomNode child = element.firstChildElement("CHILDREN").firstChild();
     while (!child.isNull()) {
         bool tableInternal = false;
         if(listView)
             parent = treeWidget->invisibleRootItem();
         QTreeWidgetItem *item = new QTreeWidgetItem(parent);
         QString specObjectID = child.firstChildElement("OBJECT").firstChild().toElement().text();
         SpecObject specObject = specObjectList.value(specObjectID);

         if(mergeTextAndChapterName){
            specObject.mergeTextAndHeading(textAttribut, headingAttribut);
         }

         QHash<QString, int>::iterator i;
         for (i = specAttributes.begin(); i != specAttributes.end(); ++i){
             item->setText(i.value(), specObject.getAttributValue(i.key()));
         }

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
            QDomNode enumDatatype = child.firstChild().firstChild();
            while (!enumDatatype.isNull()) {
                enumValues.insert(enumDatatype.toElement().attribute("IDENTIFIER"), enumDatatype.toElement().attribute("LONG-NAME"));
                enumDatatype = enumDatatype.nextSibling();
            }

        }
        child = child.nextSibling();
    }
}

void DomParser::parseSpecTypes(const QDomNode &element){
    QDomNode child = element.firstChild();
    QStringList labels;
    while (!child.isNull()) {
        if(child.toElement().tagName() == "SPEC-OBJECT-TYPE"){
            QDomNode attrDefElement = child.firstChild().firstChild();
            while (!attrDefElement.isNull()) {
                QString reqifID = attrDefElement.toElement().attribute("IDENTIFIER");
                specAttributes.insert(reqifID, specAttributes.size());
                QString longName = attrDefElement.toElement().attribute("LONG-NAME");
                labels << longName;
                if(longName == REQIF_TEXT){ //has reqif.text attribute
                    textAttribut = attrDefElement.toElement().attribute("IDENTIFIER");
                }
                if(longName == REQIF_CHAPTER_NAME){ //has reqif.chapterName
                    headingAttribut = attrDefElement.toElement().attribute("IDENTIFIER");
                }
                SpecType specType(reqifID, longName, attrDefElement.toElement().tagName(), "");
                specTypeList.append(specType);

                attrDefElement = attrDefElement.nextSibling();
            }
        }
        child = child.nextSibling();
    }
    treeWidget->setHeaderLabels(labels);

    //if text and chaptername exist and should be merged
    if(mergeTextAndChapterName && labels.contains(REQIF_TEXT) && labels.contains(REQIF_CHAPTER_NAME)){
        treeWidget->header()->hideSection(specAttributes.value(headingAttribut));
    } else {
        headingAttribut.clear();
        textAttribut.clear();
    }

    //doubles size of reqif.text column
    if(!textAttribut.isEmpty()){
        const int oldSize = treeWidget->header()->sectionSize(specAttributes.value(textAttribut));
        treeWidget->header()->resizeSection(specAttributes.value(textAttribut), 2*oldSize);
    }


}

void DomParser::parseSpecObjects(const QDomNode &element){
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        parseSpecObject(child.toElement().firstChild());
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
    QDomNode child = element.firstChild();
    QString reqifID = element.parentNode().toElement().attribute("IDENTIFIER");
    SpecObject specObject(reqifID);

    QString str;
    QTextStream stream(&str);

    while (!child.isNull()) {
        if(child.toElement().hasAttribute("THE-VALUE")){ //parses simple attributs, e.g. real, int, etc.
            specObject.addAttributValue(child.firstChildElement("DEFINITION").firstChild().toElement().text(),child.toElement().attribute("THE-VALUE"));
        }
        if(child.toElement().tagName() == "ATTRIBUTE-VALUE-XHTML"){ //parses xhtml attributes
            QDomNode xhtml = child.firstChildElement("THE-VALUE");

            replaceXhtmlObjects(xhtml);
            str.clear();
            xhtml.firstChild().save(stream, 4);
            stream.flush();
            str.replace(QString("xhtml:"), QString(""));

            specObject.addAttributValue(child.firstChildElement("DEFINITION").firstChild().toElement().text(), str);
        }

        if(child.toElement().tagName() == "ATTRIBUTE-VALUE-ENUMERATION"){ //parses enum values
            QDomNode enumValueRef = child.firstChild().firstChild();
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

QString DomParser::getTitle(){
    return title;
}

QString DomParser::getCreationTime(){
    return creationTime;
}

QString DomParser::getreqIfSourceTool(){
    return reqifSourceTool;
}

QString DomParser::getReqIfTool(){
    return reqIfTool;
}

QString DomParser::getReqIfVersion(){
    return reqifVersion;
}

void DomParser::setListView(bool viewAsList){
    listView = viewAsList;
}

void DomParser::setMerge(bool mergeTextAndChapter){
    mergeTextAndChapterName = mergeTextAndChapter;
}

QList <SpecType> DomParser::getSpecTypes(){
    return specTypeList;
}
