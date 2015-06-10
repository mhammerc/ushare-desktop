#ifndef QMLDESKTOP_H
#define QMLDESKTOP_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QSize>
#include <QScreen>
#include <QDesktopServices>
#include <QGuiApplication>
#include <QCryptographicHash>

class QmlDesktop : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QSize size READ size)

public:
    QmlDesktop(QObject * parent = 0) : QObject(parent) {}

    Q_INVOKABLE QString sha256(QString textToHash)
    {
        QByteArray byteArray;
        byteArray.append(textToHash);
        return QString(QCryptographicHash::hash(byteArray, QCryptographicHash::Sha256).toHex());
    }

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

    Q_INVOKABLE void openUrl(QString url)
    {
        QDesktopServices::openUrl(QUrl(url));
    }
};

#endif // DESKTOP_H

