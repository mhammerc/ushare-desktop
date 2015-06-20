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

#ifndef QMLENGINE_H
#define QMLENGINE_H

#include <QQmlEngine>

class QmlEngine : public QQmlEngine
{
public:
    QmlEngine(QObject * parent = 0);
};

#endif // QMLENGINE_H
