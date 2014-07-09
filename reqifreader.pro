TEMPLATE      = app
QT           += xml
QT           += widgets
CONFIG       += console
HEADERS       = domparser.h \
    specobject.h \
    mainwindow.h \
    infodialog.h \
    htmldelegate.h \
    searchdialog.h \
    spectypesoverviewdialog.h \
    spectype.h \
    rifparser.h \
    reqmodel.h \
    treeitem.h \
    parser.h \
    intdelegate.h \
    enumdelegate.h \
    datatype.h \
    reqifbaseelement.h \
    enumvalue.h \
    datedelegate.h \
    booldelegate.h \
    reqifxmlwriter.h
SOURCES       = domparser.cpp \
                main.cpp \
    specobject.cpp \
    mainwindow.cpp \
    infodialog.cpp \
    htmldelegate.cpp \
    searchdialog.cpp \
    spectypesoverviewdialog.cpp \
    spectype.cpp \
    rifparser.cpp \
    reqmodel.cpp \
    treeitem.cpp \
    parser.cpp \
    intdelegate.cpp \
    enumdelegate.cpp \
    datatype.cpp \
    reqifbaseelement.cpp \
    enumvalue.cpp \
    datedelegate.cpp \
    booldelegate.cpp \
    reqifxmlwriter.cpp

FORMS += \
    mainwindow.ui \
    infodialog.ui \
    searchdialog.ui \
    spectypesoverviewdialog.ui
