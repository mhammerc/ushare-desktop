#include "qmlengine.h"

QmlEngine::QmlEngine(QObject * parent) : QQmlEngine(parent)
{
    addImportPath(":/resources/qml-material/modules");
    addImportPath(":/resources/qml-extras/modules/");
}

