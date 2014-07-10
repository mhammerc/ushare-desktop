#ifndef SHORTCUTGETTER_H
#define SHORTCUTGETTER_H

#include <QLineEdit>
#include <QKeyEvent>
#include <iostream>

class ShortcutGetter : public QLineEdit
{
    Q_OBJECT
public:
    explicit ShortcutGetter(QWidget *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *e);

signals:

public slots:

};

#endif // SHORTCUTGETTER_H
