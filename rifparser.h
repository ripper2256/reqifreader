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
#ifndef RIFPARSER_H
#define RIFPARSER_H

#include <QTreeWidget>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <QHeaderView>
#include "domparser.h"
#include "htmldelegate.h"
#include "spectype.h"
#include "parser.h"

class RifParser : public Parser
{
public:
    RifParser(QTreeView *view, bool mergeTextAndChapter);
    ~RifParser();
    void setListView(bool viewAsList);
    void setMerge(bool mergeTextAndChapter);
    QList <SpecType> getSpecTypes();
    bool parseStructure(QDomDocument &document, QString &pathToXmlFile);

private:
    void parseRIfXmlFile(const QDomElement &element);
    void parseCoreContent(const QDomNode &element);
    void parseSpecObjects(const QDomNode &element);
    void parseSpecObject(const QDomNode &element);
    void parseSpecTypes(const QDomNode &element);
    void parseDatatypes(const QDomNode &element);
    void parseHeader(const QDomNode &element);
    void parseSpecifications(const QDomNode &element, TreeItem *parent = 0);
    void replaceXhtmlObjects(const QDomNode &element);
    void parseEnumValues(const QDomNode &element);
    void adjustHeaderSection();

    QString xmlPath;
    QString headingAttribut;
    QString textAttribut;
    static const QString RIF_TEXT;
    static const QString RIF_CHAPTER_NAME;
};

#endif // RIFPARSER_H
