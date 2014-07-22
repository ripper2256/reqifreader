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
