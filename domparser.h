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

#ifndef DOMPARSER_H
#define DOMPARSER_H

#include <specobject.h>
#include "spectype.h"
#include "parser.h"
#include "reqmodel.h"
#include <QtXml>


class DomParser : public Parser
{
public:
    DomParser(QTreeView *view, bool mergeTextAndChapter);
    ~DomParser();
    bool parseStructure(QDomDocument &document, QString &pathToXmlFile);

private:
    void setDelegates();
    void parseReqIfXmlFile(const QDomElement &element);
    void parseCoreContent(const QDomNode &element);
    void parseSpecObjects(const QDomNode &element);
    void parseSpecObject(const QDomNode &element);
    void parseSpecTypes(const QDomNode &element);
    void parseDatatypes(const QDomNode &element);
    void parseHeader(const QDomNode &element);
    void parseSpecifications(const QDomNode &element, TreeItem *parent = 0);
    void replaceXhtmlObjects(const QDomNode &element);
    void adjustHeaderSection();
    void parseEnumValues(const QDomNode & element, DataType *dataType);

    QString xmlPath;
    QString headingAttribut;
    QString textAttribut;
    static const QString REQIF_TEXT;
    static const QString REQIF_CHAPTER_NAME;
    static const QString REQIF_HTML_TYPE;
    static const QString REQIF_STRING_TYPE;
    static const QString REQIF_INT_TYPE;
    static const QString REQIF_ENUM_TYPE;
    static const QString REQIF_REAL_TYPE;
    static const QString REQIF_DATE_TYPE;
    static const QString REQIF_BOOL_TYPE;
};

#endif
