#ifndef ISHORTCUTMANAGER_H
#define ISHORTCUTMANAGER_H


#include <QObject>
#include <QKeySequence>
#include <qt_windows.h>
#include <QAbstractEventDispatcher>
#include <QAbstractNativeEventFilter>


class ShortcutManager : public QObject, public QAbstractNativeEventFilter
{
    Q_OBJECT
public:
    ShortcutManager(QKeySequence sequence, QObject * parent = 0);
    ShortcutManager(QObject * parent = 0);
    bool registerShortcut(QKeySequence shortcut);
    bool unregisterShortcut();
    quint32 nativeModifiers(Qt::KeyboardModifiers modifiers);
    quint32 nativeKeycode(Qt::Key key);
    virtual bool nativeEventFilter(const QByteArray & eventType,void * message, long * result);

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


#endif // ISHORTCUTMANAGER_H
