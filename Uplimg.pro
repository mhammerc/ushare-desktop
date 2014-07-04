QT       += core gui network multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Uplimg
TEMPLATE = app
TRANSLATIONS = uplimg_fr.ts uplimg_en.ts

QMAKE_CXXFLAGS += -std=c++11

OTHER_FILES += resources/small.png

RESOURCES += \
    resources/resources.qrc

HEADERS += \
    configuration/configurationwindows.h \
    FileDialog.h \
    configuration/ftpconfiguration.h \
    uploadMethod/ftpupload.h \
    uploadMethod/httppostupload.h \
    screenmanager.h \
    selectareaband.h \
    systemtrayicon.h \
    shared.h \
    configuration/httpconfiguration.h

SOURCES += \
    configuration/configurationwindows.cpp \
    FileDialog.cpp \
    configuration/ftpconfiguration.cpp \
    uploadMethod/ftpupload.cpp \
    uploadMethod/httppostupload.cpp \
    screenmanager.cpp \
    selectareaband.cpp \
    systemtrayicon.cpp \
    uplimg.cpp \
    configuration/httpconfiguration.cpp

INCLUDEPATH = C:\Users\Imote\Documents\Development\SFML-master\include
DEPENDPATH = C:\Users\Imote\Documents\Development\SFML-master\include
LIBS = -LC:\Users\Imote\Documents\Development\SFML-master-build-gcc-32\lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
