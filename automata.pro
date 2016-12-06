QT += core
QT -= gui

TARGET = automata
CONFIG += console c++11
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += main.cpp \
    cliquenetwork.cpp \
    cliquenetworkmanager.cpp \
    utils.cpp

HEADERS += \
    cliquenetwork.h \
    cliquenetworkmanager.h \
    utils.h

