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
