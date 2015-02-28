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

#ifdef Q_OS_LINUX
        return screen->availableVirtualSize();
#endif

#ifdef Q_OS_WIN
        return screen->availableSize();
#endif
    }
};

#endif // DESKTOP_H

