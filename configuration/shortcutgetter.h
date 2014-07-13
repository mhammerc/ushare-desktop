#ifndef SHORTCUTGETTER_H
#define SHORTCUTGETTER_H

#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>
#include <iostream>

class ConfigurationWindows;

class ShortcutGetter : public QPushButton
{
    Q_OBJECT
public:
    explicit ShortcutGetter(QWidget * widget = 0);

protected:
    ConfigurationWindows * parent;
    void keyPressEvent(QKeyEvent *e);

signals:
    void textChanged(QString);

public slots:
    void shortcutClicked();

};

#endif // SHORTCUTGETTER_H
