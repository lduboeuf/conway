#-------------------------------------------------
#
# Project created by QtCreator 2012-06-29 15:41:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = gol
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gamewidget.cpp \
    generationhistory.cpp

HEADERS  += mainwindow.h \
    gamewidget.h \
    generationhistory.h

FORMS    += mainwindow.ui

OTHER_FILES += \
    README.markdown

UBUNTU_TOUCH {
    message("building for Ubuntu Touch")

    target.path = /
    click_files.path = /
    click_files.files = $$PWD/ubuntu_touch/*
    INSTALLS+=target click_files
}
