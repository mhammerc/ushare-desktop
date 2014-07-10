#ifndef SHORTCUTGETTER_H
#define SHORTCUTGETTER_H

#include <QLineEdit>
#include <QKeyEvent>

class ShortcutGetter : public QLineEdit
{
    Q_OBJECT
public:
    explicit ShortcutGetter(QObject *parent = 0);

protected:
    void keyPressEvent(QKeyEvent *e);

signals:

public slots:

};

#endif // SHORTCUTGETTER_H
