TEMPLATE = app

CONFIG   += c++11
QMAKE_CXXFLAGS += -stdlib=libc++
QMAKE_CXXFLAGS += -mmacosx-version-min=10.7
QMAKE_CXXFLAGS += -Wall

DEFINES += QT_USE_QSTRINGBUILDER

TARGET = QtVerbalExpressions

QT -= gui
QT += core

SOURCES += \
    QVerbalExpressions.cpp \
    Tests.cpp

HEADERS += QVerbalExpressions.h
