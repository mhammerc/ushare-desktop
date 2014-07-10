#include "shortcutgetter.h"

ShortcutGetter::ShortcutGetter(QObject *parent)
{
}

void ShortcutGetter::keyPressEvent(QKeyEvent *e)
{
  switch(e->key())


    if (!isEnabled())
  {
    QLineEdit::keyPressEvent(e);
    return;
  }

  e->accept();

  if(!e->text().isEmpty())
  {
    QKeySequence sequence(e->key() | e->modifiers());
    setText(sequence.toString());
  }
}
