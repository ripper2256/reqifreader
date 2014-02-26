#ifndef PARSER_H
#define PARSER_H

#include <specobject.h>
#include "spectype.h"
#include <QtXml>

class QTreeWidget;
class QTreeWidgetItem;
class QFile;

class Parser
{
public:
    Parser();
    ~Parser();
    virtual bool parseStructure(QDomDocument &document, QString &pathToXmlFile) = 0;
    void clear();
    QString getTitle();
    QString getCreationTime();
    QString getReqIfTool();
    QString getReqIfVersion();
    QString getreqIfSourceTool();
    QList <SpecType> getSpecTypes();
    void setListView(bool viewAsList);
    void setMerge(bool mergeTextAndChapter);

protected:
    QTreeWidget *treeWidget;
    QHash<QString, int> specAttributes;
    QHash<QString, QString> enumValues;
    QHash<QString, SpecObject> specObjectList;
    QList <SpecType> specTypeList;
    QDomDocument doc;
    bool listView;
    bool mergeTextAndChapterName;
    //Header information
    QString title;
    QString creationTime;
    QString reqIfTool;
    QString reqifVersion;
    QString reqifSourceTool;
};

#endif // PARSER_H
