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

DomParser::DomParser(QTreeWidget *tree){
    treeWidget = tree;
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
    doc.clear();
}

bool DomParser::readFile(QFile &file){
    QString errorStr;
    int errorLine;
    int errorColumn;


    if (!doc.setContent(&file, false, &errorStr, &errorLine, &errorColumn)) {
        /*std::cerr << "Error: Parse error at line " << errorLine << ", "
                  << "column " << errorColumn << ": "
                  << qPrintable(errorStr) << std::endl;*/
        return false;
    }

    QDomElement root = doc.documentElement();

    if (root.tagName() != "REQ-IF") {
        //std::cerr << "Error: Not a ReqIF file" << std::endl;
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

void DomParser::parseCoreContent(const QDomNode &element){
    QDomNode child = element;
    while (!child.isNull()) {
        if (child.toElement().tagName() == "SPEC-TYPES"){
            parseSpecTypes(child.toElement());
        }
        if (child.toElement().tagName() == "SPEC-OBJECTS"){
            QTime myTimer;
            myTimer.start();
            parseSpecObjects(child.toElement());
            qDebug() << "obj";
            qDebug() << myTimer.elapsed();
        }
        if (child.toElement().tagName() == "DATATYPES"){
            parseDatatypes(child.toElement());
        }
        if (child.toElement().tagName() == "SPECIFICATIONS"){

            HTMLDelegate* delegate = new HTMLDelegate();
            treeWidget->setItemDelegate(delegate);
            treeWidget->header()->setSectionsMovable(true);
            parseSpecifications(child.toElement().firstChild(), treeWidget->invisibleRootItem());
            qDebug() << "spec";
            qDebug() << myTimer.elapsed();
        }
        child = child.nextSibling();
    }
}

void DomParser::parseSpecifications(const QDomNode &element, QTreeWidgetItem *parent){
    QDomNode child = element.firstChildElement("CHILDREN").firstChild();
     while (!child.isNull()) {
         QTreeWidgetItem *item = new QTreeWidgetItem(parent);
         QString specObjectID = child.firstChildElement("OBJECT").firstChild().toElement().text();
         SpecObject specObject = specObjectList.value(specObjectID);

         QHash<QString, int>::iterator i;
         for (i = specAttributes.begin(); i != specAttributes.end(); ++i){

             /*QWidget* w = new QWidget();

             QVBoxLayout* vbl = new QVBoxLayout(w);
             QLabel* lab_01 = new QLabel(specObject.getAttributValue(i.key()));

             vbl->addWidget(lab_01);
             vbl->setSizeConstraint(QLayout::SetNoConstraint);
             w->setLayout(vbl);
             treeWidget->setItemWidget(item,i.value(), w);*/

             //item->setData();
             item->setText(i.value(), specObject.getAttributValue(i.key()));
         }

         parseSpecifications(child, item);
         child = child.nextSibling();
     }
}

void DomParser::parseDatatypes(const QDomNode &element){
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        if (child.toElement().tagName() == "DATATYPE-DEFINITION-ENUMERATION"){
            QDomNode enumDatatype = child.firstChild().firstChild();
            while (!enumDatatype.isNull()) {
                enumValues.insert(enumDatatype.toElement().attribute("IDENTIFIER"), enumDatatype.toElement().attribute("LONG-NAME"));
                //qDebug() << enumDatatype.toElement().attribute("IDENTIFIER");
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
                specAttributes.insert(attrDefElement.toElement().attribute("IDENTIFIER"), specAttributes.size());
                labels << attrDefElement.toElement().attribute("LONG-NAME");
                attrDefElement = attrDefElement.nextSibling();
            }
            //qDebug() << child.firstChild().firstChild().toElement().attribute("LONG-NAME");
        }
        child = child.nextSibling();
    }
    treeWidget->setHeaderLabels(labels);
}

void DomParser::parseSpecObjects(const QDomNode &element){
    QDomNode child = element.firstChild();
    while (!child.isNull()) {
        parseSpecObject(child.toElement().firstChild());
        child = child.nextSibling();
    }

}


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


void DomParser::parseSpecObject(const QDomNode &element){
    QDomNode child = element.firstChild();
    //QTreeWidgetItem *item = new QTreeWidgetItem(treeWidget->invisibleRootItem());
    QString reqifID = element.parentNode().toElement().attribute("IDENTIFIER");
    SpecObject specObject(reqifID);

    while (!child.isNull()) {
        if(child.toElement().hasAttribute("THE-VALUE")){
            //int position = specAttributes.value(child.firstChildElement("DEFINITION").firstChild().toElement().text());
            //item->setText(position, child.toElement().attribute("THE-VALUE"));
            specObject.addAttributValue(child.firstChildElement("DEFINITION").firstChild().toElement().text(),child.toElement().attribute("THE-VALUE"));
        }
        if(child.toElement().tagName() == "ATTRIBUTE-VALUE-XHTML"){
            QDomNode xhtml = child.firstChildElement("THE-VALUE");

            replaceXhtmlObjects(xhtml);
            QString str;
            QTextStream stream(&str);

            xhtml.firstChild().save(stream, 4);
            str.replace(QString("xhtml:"), QString(""));

            specObject.addAttributValue(child.firstChildElement("DEFINITION").firstChild().toElement().text(), str);
        }

        if(child.toElement().tagName() == "ATTRIBUTE-VALUE-ENUMERATION"){
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


