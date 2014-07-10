QT       += core gui network multimedia widgets
CONFIG += qxt
QXT += core gui widgets

TARGET = Uplimg
TEMPLATE = app
TRANSLATIONS = uplimg_fr.ts uplimg_en.ts

QMAKE_CXXFLAGS += -std=c++11

RC_ICONS = resources/uplimg.ico

RESOURCES += \
    resources/resources.qrc \
    langs.qrc

HEADERS += \
    configuration/configurationwindows.h \
    configuration/ftpconfiguration.h \
    uploadMethod/ftpupload.h \
    uploadMethod/httppostupload.h \
    screenmanager.h \
    selectareaband.h \
    systemtrayicon.h \
    shared.h \
    configuration/httpconfiguration.h \
    configuration/shortcutgetter.h

SOURCES += \
    configuration/configurationwindows.cpp \
    configuration/ftpconfiguration.cpp \
    uploadMethod/ftpupload.cpp \
    uploadMethod/httppostupload.cpp \
    screenmanager.cpp \
    selectareaband.cpp \
    systemtrayicon.cpp \
    uplimg.cpp \
    configuration/httpconfiguration.cpp \
    configuration/shortcutgetter.cpp


INCLUDEPATH += D:\Development\SFML\SFML-master\include
DEPENDPATH += D:\Development\SFML\SFML-master\include
LIBS += -LD:\Development\SFML\SFML-master-build-gcc-32\lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d

INCLUDEPATH += D:\Development\libqxt-qt5\include
DEPENDPATH += D:\Development\libqxt-qt5\include
LIBS += -LD:\Development\libqxt-qt5\lib

CONFIG(release, debug|release): LIBS += -lQxtCore -lQxtDesignerPlugins -lQxtNetwork -lQxtSql -lQxtWeb -lQxtWidgets
CONFIG(debug, debug|release): LIBS += -lQxtCored -lQxtDesignerPluginsd -lQxtNetworkd -lQxtSqld -lQxtWebd -lQxtWidgetsd
