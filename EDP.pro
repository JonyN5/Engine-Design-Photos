#-------------------------------------------------
#
# Project created by QtCreator 2018-03-25T13:42:43
#
#-------------------------------------------------

QT       += \
    core gui\
         sql\


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = EDPbetta
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
    main.cpp \
    setapp.cpp \
    authorization_menu.cpp \
    sqlconnect.cpp \
    edpmain.cpp \
    dbviewwin.cpp \
    downloadwin.cpp \
    dw_info.cpp \
    new_combo.cpp \
    dw_insert.cpp

HEADERS += \
    setapp.h \
    authorization_menu.h \
    sqlconnect.h \
    edpmain.h \
    dbviewwin.h \
    downloadwin.h \
    dw_info.h \
    new_combo.h \
    dw_insert.h

FORMS += \
    authorization_menu.ui \
    edpmain.ui \
    dbviewwin.ui \
    downloadwin.ui \
    dw_info.ui \
    dw_insert.ui
