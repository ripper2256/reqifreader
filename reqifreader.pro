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
    parser.h
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
    parser.cpp

FORMS += \
    mainwindow.ui \
    infodialog.ui \
    searchdialog.ui \
    spectypesoverviewdialog.ui
