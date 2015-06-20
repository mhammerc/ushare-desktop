#include "shortcutgetter.h"

ShortcutGetter::ShortcutGetter(QObject *parent) : QObject(parent)
{
    qApp->installEventFilter(this);
}

bool ShortcutGetter::eventFilter(QObject *obj, QEvent *e)
{
    if(e->type() == QEvent::KeyPress)
    {
        QKeyEvent * keyEvent = static_cast<QKeyEvent*>(e);

        /* Just mod keys are not enough for a shortcut */
        if(keyEvent->key() >= Qt::Key_Shift && keyEvent->key() <= Qt::Key_Alt)
        {
            return QObject::eventFilter(obj, e);
        }

        int keyInt = keyEvent->modifiers() + keyEvent->key();

        setKey(QKeySequence(keyInt).toString());
        return false;
    }
    else
    {
        return QObject::eventFilter(obj, e);
    }
}

QString ShortcutGetter::key()
{
    return _key;
}

void ShortcutGetter::setKey(QString key)
{
    this->_key = key;
    emit keyChanged(key);
}

