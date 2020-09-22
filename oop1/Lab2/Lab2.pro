QT -= gui
QT       += core
CONFIG += c++11 console
CONFIG -= app_bundle
TARGET = Lab2

DEFINES += QT_DEPRECATED_WARNINGS

TEMPLATE = app

SOURCES += \
        complex.cpp \
        console.cpp \
        main.cpp \
        polinom.cpp


qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

HEADERS += \
    complex.h \
    console.h \
    number.h \
    polinom.h
