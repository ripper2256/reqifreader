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
    enumValuesList.clear();
    dataTypeList.clear();
    specificationTypeList.clear();
    delete model;
}

void Parser::sortSpecTypes(int position) {
    int i = 0;
    if(position != -1){
        SpecType firstST = specTypeList.at(position);
        labels << firstST.getLongName();
        specAttributes.insert(firstST.getIdentifier(), specAttributes.size());
    }
    foreach (SpecType spType, specTypeList) {
        if(i == position) {

        } else {
            labels << spType.getLongName();
            specAttributes.insert(spType.getIdentifier(), specAttributes.size());
        }
        i++;
    }

}

int Parser::sortCritieria(const QString &longName) {
    int position = -1;
    int i = 0;
    foreach (SpecType spType, specTypeList) {
        if(spType.getLongName() == longName){
            position = i;
            return position;
        }
        i++;
    }
    return position;
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

ReqModel * Parser::getReqModel() {
    return model;
}
