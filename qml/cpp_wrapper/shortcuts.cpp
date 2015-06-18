#include "shortcuts.h"

Shortcuts::Shortcuts(SystemTrayIcon *systemTrayIcon, QObject *parent) :
    QObject(parent),
    systemTrayIcon(systemTrayIcon)
{}

void Shortcuts::setFullScreen(QString key)
{
    systemTrayIcon->captureFullScreen_k = QKeySequence(key);
    systemTrayIcon->updateShortcuts();
}

void Shortcuts::setAreaScreen(QString key)
{
    systemTrayIcon->captureSelectedScreen_k = QKeySequence(key);
    systemTrayIcon->updateShortcuts();
}

void Shortcuts::setNewPaste(QString key)
{
    systemTrayIcon->makePaste_k = QKeySequence(key);
    systemTrayIcon->updateShortcuts();
}

void Shortcuts::setSendFile(QString key)
{
    systemTrayIcon->sendFile_k = QKeySequence(key);
    systemTrayIcon->updateShortcuts();
}

void Shortcuts::setSendClipboard(QString key)
{
    systemTrayIcon->sendClipboard_k = QKeySequence(key);
    systemTrayIcon->updateShortcuts();
}

void Shortcuts::enableShortcuts()
{
    systemTrayIcon->setShortcutsEnabled(true);
}

void Shortcuts::disableShortcuts()
{
    systemTrayIcon->setShortcutsEnabled(false);
}

