#-------------------------------------------------
#
# Project created by QtCreator 2018-05-08T19:03:24
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kalk
MOC_DIR = moc_dir
OBJECTS_DIR = o_dir


CONFIG += c++11
QMAKE_CXXFLAGS += -std=c++11

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
    source/main.cpp \
    source/calculator.cpp \
    source/button.cpp \
    source/menu.cpp \
    source/controller.cpp \
    source/modello.cpp \
    source/buttonop.cpp \
    source/errore.cpp \
    source/errorebinario.cpp \
    source/erroreunario.cpp \
    source/matrice.cpp \
    source/matricediagonale.cpp \
    source/matricequadrata.cpp \
    source/vettore.cpp \
    source/vettorecolonna.cpp \
    source/vettoreriga.cpp \
    source/parser.cpp

HEADERS += \
    headers/calculator.h \
    headers/button.h \
    headers/menu.h \
    headers/controller.h \
    headers/modello.h \
    headers/buttonop.h \
    headers/errore.h \
    headers/errorebinario.h \
    headers/erroreunario.h \
    headers/matrice.h \
    headers/matricediagonale.h \
    headers/matricequadrata.h \
    headers/vettore.h \
    headers/vettorecolonna.h \
    headers/vettoreriga.h \
    headers/parser.h
