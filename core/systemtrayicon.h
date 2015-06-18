#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QApplication>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <QKeySequence>

#include "core/settings.h"
#include "shortcuts/qxtglobalshortcut.h"

class SystemTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    SystemTrayIcon(QObject * parent = 0);
    SystemTrayIcon(const QIcon & icon, QObject * parent = 0);
    ~SystemTrayIcon();

    QKeySequence captureFullScreen_k;
    QKeySequence captureSelectedScreen_k;
    QKeySequence makePaste_k;
    QKeySequence sendFile_k;
    QKeySequence sendClipboard_k;

    void updateShortcuts();
    void setShortcutsEnabled(bool enabled = true);

signals:
    void openUplimgAsked();
    void captureFullScreenAsked();
    void captureSelectedScreenAsked();
    void sendFileAsked();
    void sendClipboardAsked();
    void makePasteAsked();

private:
    void init();
    void makeShortcuts();
    void makeContextMenu();
    void makeGlobalShortcuts();
    void makeConnections();

    /* Constants */
    const QString fullScreenIcon = ":/images/context_menu/fullscreen.png";
    const QString selectedScreenIcon = ":/images/context_menu/selected_screen.png";
    const QString pasteIcon = ":/images/context_menu/paste.png";
    const QString fileIcon = ":/images/context_menu/file.png";
    const QString clipboardIcon = ":/images/context_menu/clipboard.png";


    /* The menu */
    QMenu * menu;
    QAction * captureFullScreen;
    QAction * captureSelectedScreen;
    QAction * makePaste;
    QAction * sendFile;
    QAction * sendClipboard;
    QAction * openUplimgWeb;
    QAction * openUplimg;
    QAction * exitUplimg;

    /* Shortcuts */
    QxtGlobalShortcut * captureFullScreen_s;
    QxtGlobalShortcut * captureSelectedScreen_s;
    QxtGlobalShortcut * makePaste_s;
    QxtGlobalShortcut * sendFile_s;
    QxtGlobalShortcut * sendClipboard_s;

};

#endif // SYSTEMTRAYICON_H
