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

#ifndef SHORTCUTS_H
#define SHORTCUTS_H

#include <QObject>
#include <QKeySequence>

#include "core/systemtrayicon.h"

class Shortcuts : public QObject
{
    Q_OBJECT
public:
    explicit Shortcuts(SystemTrayIcon * systemTrayIcon, QObject *parent = 0);

private:
    SystemTrayIcon * systemTrayIcon;

public slots:
    Q_INVOKABLE void setFullScreen(QString key);
    Q_INVOKABLE void setAreaScreen(QString key);
    Q_INVOKABLE void setNewPaste(QString key);
    Q_INVOKABLE void setSendFile(QString key);
    Q_INVOKABLE void setSendClipboard(QString key);

    Q_INVOKABLE void enableShortcuts();
    Q_INVOKABLE void disableShortcuts();
};

#endif // SHORTCUTS_H
