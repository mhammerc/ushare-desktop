/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#ifndef SHORTCUTMANAGER_LINUX_H
#define SHORTCUTMANAGER_LINUX_H

#include <QKeySequence>
#include <QObject>
#include <QAbstractEventDispatcher>
#include <QAbstractNativeEventFilter>


class ShortcutManager : public QObject
{

public:
    ShortcutManager(QKeySequence sequence, QObject * parent = 0);
    ShortcutManager(QObject * parent = 0);
    bool registerShortcut(QKeySequence shortcut);
    bool unregisterShortcut();
    quint32 nativeModifiers(Qt::KeyboardModifiers modifiers);
    quint32 nativeKeycode(Qt::Key key);
    bool nativeeEventFilter(const QByteArray & eventType,void * message, long * result);

    QKeySequence shortcut();
    bool setShortcut(QKeySequence sequence);
    bool setDisabled(bool disabled);
    bool setEnabled(bool enabled_);

protected:
    bool enabled;

    void activateShortcut(quint32 nativeKey, quint32 nativeMods);

    QKeySequence sequence;

    quint32 nativeKey;
    quint32 nativeMods;

signals:
    void activated();
};

#endif // ISHORTCUTMANAGER_LINUX_H
