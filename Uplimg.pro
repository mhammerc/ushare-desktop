QT       += core gui network multimedia widgets

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
    configuration/shortcutgetter.h \
    filesendedsound.h \
    widgets/label.h \
    paste/pastewindow.h \
    paste/pastecontent.h \
    widgets/button.h \
    widgets/topbar.h \
    widgets/checkbox.h \
    uploadMethod/cmsuplimgupload.h \
    widgets/radiobutton.h \
    shortcut/shortcutmanager_win.h \
    uploadMethod/file.h

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
    configuration/shortcutgetter.cpp \
    filesendedsound.cpp \
    paste/pastewindow.cpp \
    uploadMethod/cmsuplimgupload.cpp \
    shortcut/shortcutmanager_win.cpp


OTHER_FILES += \
    resources/styleSheet.css


INCLUDEPATH += D:\Development\SFML\SFML-master\include
DEPENDPATH += D:\Development\SFML\SFML-master\include
LIBS += -LD:\Development\SFML\SFML-master-build-gcc-32\lib

CONFIG(release, debug|release): LIBS += -lsfml-audio -lsfml-graphics -lsfml-network -lsfml-window -lsfml-system
CONFIG(debug, debug|release): LIBS += -lsfml-audio-d -lsfml-graphics-d -lsfml-network-d -lsfml-window-d -lsfml-system-d
