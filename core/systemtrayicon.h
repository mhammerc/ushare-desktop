#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <QApplication>
#include <QSystemTrayIcon>
#include <QIcon>
#include <QMenu>
#include <QAction>
#include <QKeySequence>

#include "shortcuts/qxtglobalshortcut.h"

class SystemTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    SystemTrayIcon(QObject * parent = 0);
    SystemTrayIcon(const QIcon & icon, QObject * parent = 0);
    ~SystemTrayIcon();

signals:
    void openUplimgAsked();

private:
    void init();
    void makeContextMenu();

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
