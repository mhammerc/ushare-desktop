/**
 * This file (c) by : - Martin Hammerchmidt alias Imote
 *
 * This file is licensed under a
 * GNU GENERAL PUBLIC LICENSE V3.0
 *
 * See the LICENSE file to learn more.
 *
 * If you have contributed to this file, add your name to authors list.
*/

#include "systemtrayicon.h"
#include <iostream>

SystemTrayIcon::SystemTrayIcon(QObject* parent)
    : QSystemTrayIcon(parent)
{
    init();
}

SystemTrayIcon::SystemTrayIcon(const QIcon &icon, QObject* parent)
    : QSystemTrayIcon(icon, parent)
{
    init();
}

SystemTrayIcon::~SystemTrayIcon()
{
}

void SystemTrayIcon::init()
{
    setIcon(QIcon(":/images/ushare_icon.png"));
    setToolTip("uShare - let's go!");
    makeShortcuts();
    makeContextMenu();
    makeGlobalShortcuts();
    makeConnections();
}

void SystemTrayIcon::makeShortcuts()
{
    if(Settings::entry(SettingsKeys::SHORTCUT_FULLSCREEN).isNull())
    {
        Settings::setEntry(SettingsKeys::SHORTCUT_FULLSCREEN, "ALT+1");
        Settings::setEntry(SettingsKeys::SHORTCUT_AREASCREEN, "ALT+2");
        Settings::setEntry(SettingsKeys::SHORTCUT_NEWPASTE, "ALT+3");
        Settings::setEntry(SettingsKeys::SHORTCUT_SENDFILE, "ALT+4");
        Settings::setEntry(SettingsKeys::SHORTCUT_SENDCLIPBOARD, "ALT+5");
    }

    captureFullScreen_k = QKeySequence(Settings::entry(SettingsKeys::SHORTCUT_FULLSCREEN).toString());
    captureSelectedScreen_k = QKeySequence(Settings::entry(SettingsKeys::SHORTCUT_AREASCREEN).toString());
    makePaste_k = QKeySequence(Settings::entry(SettingsKeys::SHORTCUT_NEWPASTE).toString());
    sendFile_k = QKeySequence(Settings::entry(SettingsKeys::SHORTCUT_SENDFILE).toString());
    sendClipboard_k = QKeySequence(Settings::entry(SettingsKeys::SHORTCUT_SENDCLIPBOARD).toString());
}

void SystemTrayIcon::makeContextMenu()
{
    /* Make the menu by it self */
    menu = new QMenu();
    menu->setTearOffEnabled(true);

    captureFullScreen = menu->addAction(QIcon(fullScreenIcon), tr("Capture fullscreen"));
    captureFullScreen->setShortcut(captureFullScreen_k);

    captureSelectedScreen = menu->addAction(QIcon(selectedScreenIcon), tr("Capture selected area"));
    captureSelectedScreen->setShortcut(captureSelectedScreen_k);

    makePaste = menu->addAction(QIcon(pasteIcon), tr("Cook new paste"));
    makePaste->setShortcut(makePaste_k);

    sendFile = menu->addAction(QIcon(fileIcon), tr("Send new file"));
    sendFile->setShortcut(sendFile_k);

    sendClipboard = menu->addAction(QIcon(clipboardIcon), tr("Send clipboard"));
    sendClipboard->setShortcut(sendClipboard_k);

    menu->addSeparator();

    openUplimgWeb = menu->addAction(tr("Open online dashboard"));
    openUplimg = menu->addAction(tr("Open the app"));

    menu->addSeparator();

    exitUplimg = menu->addAction("Exit uShare");

    QAction * build = menu->addAction("Beta 0.0.2");
    build->setDisabled(true);

    setContextMenu(menu);
}

void SystemTrayIcon::makeGlobalShortcuts()
{
    /* Then we set up global shortcuts */

    captureFullScreen_s = new QxtGlobalShortcut(captureFullScreen_k, this);
    captureSelectedScreen_s = new QxtGlobalShortcut(captureSelectedScreen_k, this);
    makePaste_s = new QxtGlobalShortcut(makePaste_k, this);
    sendFile_s = new QxtGlobalShortcut(sendFile_k, this);
    sendClipboard_s = new QxtGlobalShortcut(sendClipboard_k, this);

    QObject::connect(captureFullScreen_s, &QxtGlobalShortcut::activated, captureFullScreen, &QAction::trigger);
    QObject::connect(captureSelectedScreen_s, &QxtGlobalShortcut::activated, captureSelectedScreen, &QAction::trigger);
    QObject::connect(makePaste_s, &QxtGlobalShortcut::activated, makePaste, &QAction::trigger);
    QObject::connect(sendFile_s, &QxtGlobalShortcut::activated, sendFile, &QAction::trigger);
    QObject::connect(sendClipboard_s, &QxtGlobalShortcut::activated, sendClipboard, &QAction::trigger);
}

void SystemTrayIcon::updateShortcuts()
{
    captureFullScreen_s->setShortcut(captureFullScreen_k);
    captureSelectedScreen_s->setShortcut(captureSelectedScreen_k);
    makePaste_s->setShortcut(makePaste_k);
    sendFile_s->setShortcut(sendFile_k);
    sendClipboard_s->setShortcut(sendClipboard_k);

    captureFullScreen->setShortcut(captureFullScreen_k);
    captureSelectedScreen->setShortcut(captureSelectedScreen_k);
    makePaste->setShortcut(makePaste_k);
    sendFile->setShortcut(sendFile_k);
    sendClipboard->setShortcut(sendClipboard_k);
}

void SystemTrayIcon::setShortcutsEnabled(bool enabled)
{
    captureFullScreen_s->setEnabled(enabled);
    captureSelectedScreen_s->setEnabled(enabled);
    makePaste_s->setEnabled(enabled);
    sendFile_s->setEnabled(enabled);
    sendClipboard_s->setEnabled(enabled);
}

void SystemTrayIcon::makeConnections()
{
    /* Now, we need to connect this menu */

    QObject::connect(captureFullScreen, &QAction::triggered, this, &SystemTrayIcon::captureFullScreenAsked);
    QObject::connect(captureSelectedScreen, &QAction::triggered, this, &SystemTrayIcon::captureSelectedScreenAsked);
    QObject::connect(sendFile, &QAction::triggered, this, &SystemTrayIcon::sendFileAsked);
    QObject::connect(sendClipboard, &QAction::triggered, this, &SystemTrayIcon::sendClipboardAsked);
    QObject::connect(makePaste, &QAction::triggered, this, &SystemTrayIcon::makePasteAsked);
    QObject::connect(openUplimg, &QAction::triggered, this, &SystemTrayIcon::openUplimgAsked);
    QObject::connect(exitUplimg, &QAction::triggered, qApp, &QApplication::quit);
    QObject::connect(this, &QSystemTrayIcon::messageClicked, this, &SystemTrayIcon::openLastFile);

    QObject::connect(this, &QSystemTrayIcon::activated, [this](QSystemTrayIcon::ActivationReason reason)
    {
       if(reason == QSystemTrayIcon::Trigger)
       {
           emit openLastFile();
       }
       else if(reason == QSystemTrayIcon::DoubleClick)
       {
           emit openUplimgAsked();
       }
    });
}
