#ifndef QMLDESKTOP_H
#define QMLDESKTOP_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QSize>
#include <QScreen>
#include <QDesktopServices>
#include <QGuiApplication>

class QmlDesktop : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QSize size READ size)

public:
    QmlDesktop(QObject * parent = 0) : QObject(parent) {}

    QSize size()
    {
        QScreen * screen = QGuiApplication::primaryScreen();
        return screen->availableVirtualSize();
    }

    Q_INVOKABLE void openUrl(QString url)
    {
        QDesktopServices::openUrl(QUrl(url));
    }
};

#endif // DESKTOP_H

