#-------------------------------------------------
#
# Project created by QtCreator 2018-07-04T16:10:19
#
#-------------------------------------------------

QT       += core gui
QT			 += serialport
QT			 += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

include(QXlsx/xlsx/qtxlsx.pri)

TARGET = RM_STR
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


SOURCES += main.cpp \
        rm_str.cpp \
    RLC/rlcmodule.cpp \
    SUB20/spimodule.cpp \
    switchbutton.cpp \
    wdatabase.cpp \
    devicestr.cpp \
    shedulerstr.cpp \
    DB/databasemodule.cpp \
    indicator.cpp \
    dialogaddpoint.cpp \
    dialogaddlink.cpp \
    dialogsettings.cpp \
    wmanualcontrol.cpp \
    wautocontrol.cpp \
    Proc/proc.cpp \
    wproc.cpp

HEADERS +=  rm_str.h \
    RLC/rlcmodule.h \
    SUB20/libsub.h \
    SUB20/spimodule.h \
    csys.h \
    switchbutton.h \
    wdatabase.h \
    devicestr.h \
    shedulerstr.h \
    DB/databasemodule.h \
    indicator.h \
    dialogaddpoint.h \
    dialogaddlink.h \
    dialogsettings.h \
    wmanualcontrol.h \
    wautocontrol.h \
    Proc/proc.h \
    wproc.h

FORMS += rm_str.ui \
    wdatabase.ui \
    dialogaddpoint.ui \
    dialogaddlink.ui \
    dialogsettings.ui \
    wmanualcontrol.ui \
    wautocontrol.ui \
		wproc.ui



 win32 {
		 LIBS += "D:\Cloud Mail.Ru\Topaz-Work\RM_STR\RM_STR\RM_STR\SUB20\sub20.lib"
 }

 unix {
		LIBS += "/home/jitarciuk/Cloud/Topaz-Work/RM_STR/RM_STR/RM_STR/SUB20/libsub.so"
 }


RESOURCES += res.qrc

DISTFILES += version.txt
