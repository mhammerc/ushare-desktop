#ifndef QMLENGINE_H
#define QMLENGINE_H

#include <QQmlEngine>

class QmlEngine : public QQmlEngine
{
public:
    QmlEngine(QObject * parent = 0);
};

#endif // QMLENGINE_H
