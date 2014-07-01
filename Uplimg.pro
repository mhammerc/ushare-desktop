QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Uplimg
TEMPLATE = app

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += small.png

RESOURCES += \
    resources.qrc

HEADERS += \
    configurationwindows.h \
    FileDialog.h \
    ftpconfiguration.h \
    ftpupload.h \
    HTTPConfiguration.h \
    httppostupload.h \
    screenmanager.h \
    selectareaband.h \
    systemtrayicon.h \
    shared.h

SOURCES += \
    configurationwindows.cpp \
    FileDialog.cpp \
    ftpconfiguration.cpp \
    ftpupload.cpp \
    HTTPConfiguration.cpp \
    httppostupload.cpp \
    screenmanager.cpp \
    selectareaband.cpp \
    systemtrayicon.cpp \
    uplimg.cpp

INCLUDEPATH = C:\Users\Imote\Documents\Development\SFML-master\include
DEPENDPATH = C:\Users\Imote\Documents\Development\SFML-master\include
LIBS = -LC:\Users\Imote\Documents\Development\SFML-master-build-gcc-32\lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
