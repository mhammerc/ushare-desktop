/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#ifndef SHORTCUTGETTER_H
#define SHORTCUTGETTER_H

#include <QLineEdit>
#include <QPushButton>
#include <QKeyEvent>
#include <iostream>
#include "shared.h"

class ConfigurationWindows;

class ShortcutGetter : public ButtonBlue
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
