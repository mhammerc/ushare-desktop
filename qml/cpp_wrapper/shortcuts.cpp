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

