#include "shortcutgetter.h"

ShortcutGetter::ShortcutGetter(QWidget *parent) : QLineEdit(parent)
{
}

void ShortcutGetter::keyPressEvent(QKeyEvent *e)
{
    int key;

    switch(e->key())
        {
        case 38: //&
            key = Qt::Key_1;
            break;
        case 201: //E with accent (/)
            key = Qt::Key_2;
            break;
        case 34: //"
            key = Qt::Key_3;
            break;
        case 39: //'
            key = Qt::Key_4;
            break;
        case 40: //(
            key = Qt::Key_5;
            break;
        case 45: //-
            key = Qt::Key_6;
            break;
        case 200: //E with other accent (\)
            key = Qt::Key_7;
            break;
        case 95: //underscore
            key = Qt::Key_8;
            break;
        case 199: //cedilla
            key = Qt::Key_9;
            break;
        case 192: //A with accent (\)
            key = Qt::Key_0;
            break;
        default:
            key = e->key();
            break;
        }


    if (!isEnabled())
        {
            QLineEdit::keyPressEvent(e);
            return;
        }

    e->accept();

    if(!e->text().isEmpty())
        {
            QKeySequence sequence(key | e->modifiers());
            setText(sequence.toString());
        }
}
