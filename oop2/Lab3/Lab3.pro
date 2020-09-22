#---------------------------------------------------
#
# Project created by QtCreator 2020-04-03T 17:54:07
#        Ardasenov Dmitry Georgievich
#
#---------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Lab3
TEMPLATE = app


DEFINES += QT_DEPRECATED_WARNINGS



CONFIG += c++11

SOURCES += \
        complex.cpp \
        main.cpp \
        mainwindow.cpp \
        polinom.cpp

HEADERS += \
        complex.h \
        mainwindow.h \
        number.h \
        polinom.h

FORMS += \
        mainwindow.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
