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

#include "reqifbaseelement.h"

ReqIfBaseElement::ReqIfBaseElement(){

}

ReqIfBaseElement::ReqIfBaseElement(const QString &reqifID, const QString &name){
    identifier = reqifID;
    longName = name;
}

QString ReqIfBaseElement::getIdentifier(){
    return identifier;
}

QString ReqIfBaseElement::getLongName(){
    return longName;
}
