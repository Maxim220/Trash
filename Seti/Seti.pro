TEMPLATE = app
CONFIG += console c++11
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    functions.cpp \
    hemming.cpp \
    allias.cpp \
    crypto.cpp

HEADERS += \
    functions.h \
    hemming.h \
    allias.h \
    crypto.h
