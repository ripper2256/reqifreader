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

#ifndef PARSER_H
#define PARSER_H

#include <specobject.h>
#include "spectype.h"
#include "reqmodel.h"
#include "datatype.h"
#include "enumvalue.h"
#include <QtXml>
#include <QTreeView>

class QTreeWidget;
class QTreeWidgetItem;
class QFile;

class Parser
{
public:
    Parser(QTreeView *view, bool mergeTextAndChapter);
    ~Parser();
    virtual bool parseStructure(QDomDocument &document, QString &pathToXmlFile) = 0;
    void clear();
    QString getTitle();
    QString getCreationTime();
    QString getReqIfTool();
    QString getReqIfVersion();
    QString getreqIfSourceTool();
    QList <SpecType> getSpecTypes();
    QHash<QString, DataType> getDataTypes();
    ReqModel * getReqModel();

    void setListView(bool viewAsList);
    void setMerge(bool mergeTextAndChapter);

protected:
    int sortCritieria(const QString &longName);
    void sortSpecTypes(int position);

    QTreeView *treeView;
    ReqModel *model;
    QStringList labels;
    QHash<QString, int> specAttributes;
    QHash<QString, QString> enumValues;
    QHash<QString, EnumValue> enumValuesList;
    QHash<QString, SpecObject> specObjectList;
    QHash<QString, DataType> dataTypeList;

    QList<ReqIfBaseElement> specificationTypeList;
    QList <SpecType> specTypeList;
    QDomDocument doc;
    bool mergeTextAndChapterName;
    //Header information
    QString title;
    QString creationTime;
    QString reqIfTool;
    QString reqifVersion;
    QString reqifSourceTool;
};

#endif // PARSER_H
