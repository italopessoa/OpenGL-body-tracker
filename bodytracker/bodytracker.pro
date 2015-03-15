TEMPLATE = app
CONFIG += console
CONFIG -= app_bundle
CONFIG -= qt

SOURCES += main.cpp \
    objeto3d.cpp \
    matriz.cpp
LIBS += -lGL -lGLU -lglut

include(deployment.pri)
qtcAddDeployment()

HEADERS += \
    objeto3d.h \
    matriz.h

