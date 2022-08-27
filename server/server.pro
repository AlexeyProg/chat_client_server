QT       += core network gui

CONFIG += C++11
QMAKE_CXXFLAGS = -std=c++11

TARGET = server
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp

HEADERS += \
    server.h

FORMS +=
