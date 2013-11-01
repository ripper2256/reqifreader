TEMPLATE      = app
QT           += xml
QT           += widgets
CONFIG       += console
HEADERS       = domparser.h \
    specobject.h \
    mainwindow.h \
    infodialog.h \
    htmldelegate.h \
    searchdialog.h
SOURCES       = domparser.cpp \
                main.cpp \
    specobject.cpp \
    mainwindow.cpp \
    infodialog.cpp \
    htmldelegate.cpp \
    searchdialog.cpp

FORMS += \
    mainwindow.ui \
    infodialog.ui \
    searchdialog.ui
