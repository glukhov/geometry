QT       += core gui

TARGET = geo1
CONFIG   += console

TEMPLATE = app


SOURCES += src/algo/main.cpp \
    src/gui/MainWidget.cpp \
    src/gui/Drawer.cpp \
    src/objects/Point2D.cpp \
    src/algo/merge_hull.cpp

HEADERS += \
    src/gui/MainWidget.h \
    src/gui/Drawer.h \
    src/objects/Graph.h \
    src/objects/Point2D.h \
    src/algo/PolygonInputParser.h \
    src/algo/merge_hull.h
