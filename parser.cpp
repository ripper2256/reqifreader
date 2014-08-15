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
