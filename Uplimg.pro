TEMPLATE = app

QT += widgets qml quick core gui multimedia

SOURCES += main.cpp \
    core/systemtrayicon.cpp \
    uplimg.cpp \
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
    windows/pastewindow.cpp

RESOURCES += qml.qrc \
    images.qrc \
    sounds.qrc

QMAKE_CXXFLAGS += -std=c++11 # C++11 for sure !
QMAKE_CXXFLAGS += -lX11

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

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
    qml/components/functions.js \
    qml/main_window/Uploads.qml \
    qml/main_window/settings/Credits.qml \
    qml/notification_window/NotificationWindow.qml \
    qml/components/network.js \
    qml/components/md5.js \
    qml/components/Badge.qml \
    qml/components/usquare_online.js \
    qml/components/ColorPicker.qml \
    qml/components/Login.qml \
    qml/components/Dialog.qml \
    qml/components/FileCard.qml \
    qml/components/Offline.qml \
    qml/components/Loading.qml \
    qml/main_window/global/Global.qml \
    qml/components/Register.qml \
    qml/pastes/PasteWindow.qml

HEADERS += \
    core/systemtrayicon.h \
    uplimg.h \
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
    qml/cpp_wrapper/platformdetails.h \
    windows/notificationwindow.h \
    qml/cpp_wrapper/desktop.h \
    core/shared.h \
    qml/cpp_wrapper/clipboard.h \
    windows/pastewindow.h

# Global shortcuts from the Qxt Team !
HEADERS += \
    shortcuts/qxtglobalshortcut.h \
    shortcuts/qxtglobalshortcut_p.h

SOURCES += \
    shortcuts/qxtglobalshortcut.cpp \

win32 {
    SOURCES += shortcuts/win/qxtglobalshortcut_win.cpp
}

linux {
    SOURCES += shortcuts/x11/qxtglobalshortcut_x11.cpp
    LIBS += -lX11
}

mac {
    SOURCES += shortcuts/mac/qxtglobalshortcut_mac.cpp
}
