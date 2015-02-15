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
    setIcon(QIcon(":/images/uplimg_icon.png"));
    setToolTip("Uplimg");
    makeContextMenu();
    makeGlobalShortcuts();
    makeConnections();
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

    makePaste = menu->addAction(tr("Cook new paste"));
    makePaste->setShortcut(makePaste_k);

    sendFile = menu->addAction(QIcon(fileIcon), tr("Send new file"));
    sendFile->setShortcut(sendFile_k);

    sendClipboard = menu->addAction(QIcon(clipboardIcon), tr("Send clipboard"));
    sendClipboard->setShortcut(sendClipboard_k);

    menu->addSeparator();

    openUplimgWeb = menu->addAction(tr("Open online dashboard"));
    openUplimg = menu->addAction(tr("Open the app"));

    menu->addSeparator();

    exitUplimg = menu->addAction("Exit Uplimg");

    setContextMenu(menu);
}

void SystemTrayIcon::makeGlobalShortcuts()
{
    /* Then we set up global shortcuts */

    captureFullScreen_s = new QxtGlobalShortcut(captureFullScreen_k);
    captureSelectedScreen_s = new QxtGlobalShortcut(captureSelectedScreen_k);
    makePaste_s = new QxtGlobalShortcut(makePaste_k);
    sendFile_s = new QxtGlobalShortcut(sendFile_k);
    sendClipboard_s = new QxtGlobalShortcut(sendClipboard_k);

    QObject::connect(captureFullScreen_s, &QxtGlobalShortcut::activated, captureFullScreen, &QAction::trigger);
    QObject::connect(captureSelectedScreen_s, &QxtGlobalShortcut::activated, captureSelectedScreen, &QAction::trigger);
    QObject::connect(makePaste_s, &QxtGlobalShortcut::activated, makePaste, &QAction::trigger);
    QObject::connect(sendFile_s, &QxtGlobalShortcut::activated, sendFile, &QAction::trigger);
    QObject::connect(sendClipboard_s, &QxtGlobalShortcut::activated, sendClipboard, &QAction::trigger);
}

void SystemTrayIcon::makeConnections()
{
    /* Now, we need to connect this menu */

    QObject::connect(captureFullScreen, &QAction::triggered, this, &SystemTrayIcon::captureFullScreenAsked);
    QObject::connect(captureSelectedScreen, &QAction::triggered, this, &SystemTrayIcon::captureSelectedScreenAsked);
    QObject::connect(openUplimg, &QAction::triggered, this, &SystemTrayIcon::openUplimgAsked);
    QObject::connect(exitUplimg, &QAction::triggered, qApp, &QApplication::quit);
}
