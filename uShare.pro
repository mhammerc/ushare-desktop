#
#  This file (c) by : - Martin Hammerchmidt alias Imote
#
#  This file is licensed under a
#  GNU GENERAL PUBLIC LICENSE V3.0
#
#  See the LICENSE file to learn more.
#
#  If you have contributed to this file, add your name to authors list.
#

TEMPLATE = app

CONFIG += qtquickcompiler

QT += widgets qml quick core gui multimedia svg network

static {
LIBS += /usr/local/Qt-5.4.2/qml/QtQuick/PrivateWidgets/libwidgetsplugin.a
}

SOURCES += main.cpp \
    core/systemtrayicon.cpp \
    windows/mainwindow.cpp \
    core/screentaker.cpp \
    core/areauserdefiner.cpp \
    network/httpsender.cpp \
    file/filemanager.cpp \
    network/filesender.cpp \
    windows/uploadingwindow.cpp \
    core/settings.cpp \
    qml/cpp_wrapper/qmlsettings.cpp \
    sounds/filesendedsound.cpp \
    windows/notificationwindow.cpp \
    core/shared.cpp \
    windows/pastewindow.cpp \
    windows/qmlengine.cpp \
    ushare.cpp \
    qml/cpp_wrapper/ushareonline.cpp \
    qml/cpp_wrapper/shortcutgetter.cpp \
    qml/cpp_wrapper/shortcuts.cpp

RESOURCES += \
    sounds.qrc \
    translations.qrc \
    qml.qrc \
    materialdesign.qrc \
    images.qrc

DISTFILES += \
    qml/main_window/Overview.qml \
    qml/upload_window/UploadWindow.qml \
    qml/main_window/SettingsPage.qml \
    qml/main_window/settings/General.qml \
    qml/main_window/main.qml \
    qml/components/Label.qml \
    qml/components/Checkbox.qml \
    qml/main_window/settings/Saving.qml \
    qml/components/Slider.qml \
    qml/main_window/Uploads.qml \
    qml/main_window/settings/Credits.qml \
    qml/notification_window/NotificationWindow.qml \
    qml/components/Badge.qml \
    qml/components/ColorPicker.qml \
    qml/components/Login.qml \
    qml/components/Dialog.qml \
    qml/components/FileCard.qml \
    qml/components/Offline.qml \
    qml/components/Loading.qml \
    qml/components/Register.qml \
    qml/pastes/PasteWindow.qml \
    qml/main_window/settings/Updates.qml \
    qml/main_window/settings/Keyboardshortcuts.qml \
    qml/components/ProfileCard.qml

HEADERS += \
    core/systemtrayicon.h \
    windows/mainwindow.h \
    core/screentaker.h \
    core/areauserdefiner.h \
    network/httpsender.h \
    file/filemanager.h \
    file/file.h \
    core/utils.h \
    network/filesender.h \
    windows/uploadingwindow.h \
    core/settings.h \
    core/keys_data.h \
    qml/cpp_wrapper/qmlsettings.h \
    sounds/filesendedsound.h \
    windows/notificationwindow.h \
    qml/cpp_wrapper/desktop.h \
    core/shared.h \
    qml/cpp_wrapper/clipboard.h \
    windows/pastewindow.h \
    windows/qmlengine.h \
    ushare.h \
    qml/cpp_wrapper/ushareonline.h \
    qml/cpp_wrapper/shortcutgetter.h \
    qml/cpp_wrapper/shortcuts.h

# Global shortcuts from the Qxt Team !
HEADERS += \
    shortcuts/qxtglobalshortcut.h \
    shortcuts/qxtglobalshortcut_p.h

SOURCES += \
    shortcuts/qxtglobalshortcut.cpp \

# Translations

lupdate_only {
    SOURCES += qml/main_window/settings/*.qml \
        qml/main_window/*.qml \
        qml/components/*.qml \
        qml/notification_window/*.qml \
        qml/pastes/*.qml \
        qml/upload_window/*.qml
}

TRANSLATIONS = ushare_fr.ts \
    ushare_sp.ts

win32 {
    SOURCES += shortcuts/win/qxtglobalshortcut_win.cpp
    LIBS += -luser32
}

linux {
    SOURCES += shortcuts/x11/qxtglobalshortcut_x11.cpp
    LIBS += -lX11

    QMAKE_CXXFLAGS += -std=c++11 # C++11 for sure !
    QMAKE_CXXFLAGS += -lX11
}

mac {
    SOURCES += shortcuts/mac/qxtglobalshortcut_mac.cpp
}
