#include "parser.h"
#include <QTreeWidget>

Parser::Parser(QTreeView *view, bool mergeTextAndChapter){
    treeView = view;
    mergeTextAndChapterName = mergeTextAndChapter;
    model = new ReqModel();
}

Parser::~Parser(){
    clear();
}

void Parser::clear(){
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

QHash<QString, DataType> Parser::getDataTypes(){
    return dataTypeList;
}

void Parser::setMerge(bool mergeTextAndChapter){
    mergeTextAndChapterName = mergeTextAndChapter;
}
