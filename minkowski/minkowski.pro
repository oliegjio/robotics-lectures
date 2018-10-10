QT += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = minkowski
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += \
    main.cpp \
    mainwindow.cpp \
    drawable.cpp \
    shape.cpp

HEADERS += \
    mainwindow.h \
    drawable.h \
    shape.h
