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

#include "qmlengine.h"

QmlEngine::QmlEngine(QObject * parent) : QQmlEngine(parent)
{
    addImportPath(":/resources/qml-material/modules");
    addImportPath(":/resources/qml-extras/modules");
}

