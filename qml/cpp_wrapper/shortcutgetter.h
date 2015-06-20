/**
 * This file (c) by : - Martin Hammerchmidt alias Imote
 *
 * This file is licensed under a
 * GNU GENERAL PUBLIC LICENSE V3.0
 *
 * See the LICENSE file to learn more.
 *
 * If you have contributed to this file, add your name to authors list.
*/

#ifndef SHORTCUTGETTER_H
#define SHORTCUTGETTER_H

#include <QApplication>
#include <QObject>
#include <QKeyEvent>

class ShortcutGetter : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString key READ key NOTIFY keyChanged)
public:
    explicit ShortcutGetter(QObject *parent = 0);

    QString key();

    bool eventFilter(QObject * obj, QEvent * e);

private:
    void setKey(QString key);

    QString _key;

signals:
    void keyChanged(QString key);

public slots:
};

#endif // SHORTCUTGETTER_H
