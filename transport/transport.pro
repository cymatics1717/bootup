######################################################################
# Automatically generated by qmake (3.1) Fri Jul 20 07:05:09 2019
######################################################################

TEMPLATE = lib
TARGET = transport
INCLUDEPATH += .

QT += core network serialport

CONFIG += dll c++11
CONFIG += staticlib


# You can make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# Please consult the documentation of the deprecated API in order to know
# how to port your code away from it.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

# Input
HEADERS += serialpeer.hpp udpclient.hpp udpserver.hpp
SOURCES += serialpeer.cpp udpclient.cpp udpserver.cpp