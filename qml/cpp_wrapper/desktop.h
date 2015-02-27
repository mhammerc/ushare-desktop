#ifndef DESKTOP_H
#define DESKTOP_H

#include <QObject>
#include <QSize>
#include <QScreen>
#include <QGuiApplication>

class Desktop : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QSize size READ size)

public:
    Desktop(QObject * parent = 0) : QObject(parent) {}

    QSize size()
    {
        QScreen * screen = QGuiApplication::primaryScreen();
        return screen->availableVirtualSize();
    }
};

#endif // DESKTOP_H

