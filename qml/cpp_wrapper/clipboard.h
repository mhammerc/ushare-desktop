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

#ifndef DESKTOP_H
#define DESKTOP_H

#include <QApplication>
#include <QObject>
#include <QString>
#include <QClipboard>

class Clipboard : public QObject
{
    Q_OBJECT

public:
    Clipboard(QObject * parent = 0) : QObject(parent) {}

    Q_INVOKABLE void setText(QString text)
    {
        QClipboard * clipboard = QApplication::clipboard();
        clipboard->setText(text);
    }
};

#endif // DESKTOP_H

