#include "parser.h"
#include <QTreeWidget>

Parser::Parser()
{
}

Parser::~Parser(){
    clear();
}

void Parser::clear(){
    treeWidget->clear();
    treeWidget->setColumnCount(0);
    specAttributes.clear();
    enumValues.clear();
    specObjectList.clear();
    specTypeList.clear();
    doc.clear();
}

QString Parser::getTitle(){
    return title;
}

QString Parser::getCreationTime(){
    return creationTime;
}

QString Parser::getreqIfSourceTool(){
    return reqifSourceTool;
}

QString Parser::getReqIfTool(){
    return reqIfTool;
}

QString Parser::getReqIfVersion(){
    return reqifVersion;
}

QList <SpecType> Parser::getSpecTypes(){
    return specTypeList;
}

void Parser::setListView(bool viewAsList){
    listView = viewAsList;
}

void Parser::setMerge(bool mergeTextAndChapter){
    mergeTextAndChapterName = mergeTextAndChapter;
}
