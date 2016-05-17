#-------------------------------------------------
#
# Project created by QtCreator 2016-04-17T23:34:07
#
#-------------------------------------------------

QT       += core gui multimedia multimediawidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = VideoWall
TEMPLATE = app


SOURCES += main.cpp\
        dialog.cpp \
    sleeper.cpp \
    parser.cpp \
    player.cpp

HEADERS  += dialog.h \
    sleeper.h \
    parser.h \
    player.h

FORMS    += dialog.ui
