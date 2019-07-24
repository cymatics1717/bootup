######################################################################
# Automatically generated by qmake (3.1) Fri Jul 12 09:26:21 2019
######################################################################

TEMPLATE = app
TARGET = bootup

QT += quick network serialport
CONFIG += c++11


QMAKE_LFLAGS += -rdynamic

QML_IMPORT_PATH =

# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

INCLUDEPATH += . src/utils/jsoncpp src/utils/logging
INCLUDEPATH += ../transport

# Input
HEADERS += src/utils/logging/logging.hpp \
    src/utils/jsoncpp/json/json-forwards.h \
    src/utils/jsoncpp/json/json.h

SOURCES += src/utils/logging/logging.cpp \
    src/main.cpp \
    src/utils/jsoncpp/jsoncpp.cpp

RESOURCES +=  main.qrc

TRANSLATIONS += lang/en_us.ts lang/zh_CN.ts
LIBS += -L../lib -ltransport
