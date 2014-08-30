/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#include "shortcut/shortcutmanager_linux.h"

ShortcutManager::ShortcutManager(QKeySequence sequence, QObject * parent) : QObject(parent), sequence(sequence)
{
    enabled = false;
    enabled = registerShortcut(sequence);
}

ShortcutManager::ShortcutManager(QObject *parent) : QObject(parent)
{
    enabled = false;
}

QKeySequence ShortcutManager::shortcut()
{
    return sequence;
}

bool ShortcutManager::setShortcut(QKeySequence sequence)
{
    if(enabled)
    {
        unregisterShortcut();
        enabled = false;
    }

    this->sequence = sequence;
    enabled = registerShortcut(sequence);
    return enabled;
}

bool ShortcutManager::setDisabled(bool disabled)
{
    if(disabled)
        {
            unregisterShortcut();
            enabled = false;
            return true;
        }

    if(!disabled)
    {
        if(enabled)
            return true;
        if(!enabled)
        {
            enabled = registerShortcut(sequence);
            return enabled;
        }
    }

    return false;
}

bool ShortcutManager::setEnabled(bool enabled_)
{
    if(enabled_)
    {
        if(enabled)
            return true;
        if(!enabled)
        {
            enabled = registerShortcut(sequence);
            return enabled;
        }
    }

    if(!enabled_)
    {
        if(!enabled)
            return true;
        if(enabled)
        {
            unregisterShortcut();
            return true;
        }
    }
    return false;
}

bool ShortcutManager::registerShortcut(QKeySequence shortcut)
{
    return true;
}

bool ShortcutManager::unregisterShortcut()
{
    return true;
}

quint32 ShortcutManager::nativeModifiers(Qt::KeyboardModifiers modifiers)
{
    return 2;
}

quint32 ShortcutManager::nativeKeycode(Qt::Key key)
{
        return 0;
}

bool ShortcutManager::nativeeEventFilter(const QByteArray & eventType,
    void * message, long * result)
{
        return false;
}

void ShortcutManager::activateShortcut(quint32 nativeKey, quint32 nativeMods)
{

}
