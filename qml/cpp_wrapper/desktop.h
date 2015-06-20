#ifndef QMLDESKTOP_H
#define QMLDESKTOP_H

#include <QApplication>
#include <QObject>
#include <QString>
#include <QUrl>
#include <QSize>
#include <QScreen>
#include <QDesktopServices>
#include <QGuiApplication>
#include <QCryptographicHash>
#include <QRegExp>
#include <cmath>

class QmlDesktop : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QSize size READ size)

private:
    QString units1[8];
    QString units2[8];

public:
    QmlDesktop(QObject * parent = 0) : QObject(parent),
        units1 {"kB","MB","GB","TB","PB","EB","ZB","YB"},
        units2 {"KiB","MiB","GiB","TiB","PiB","EiB","ZiB","YiB"}
    {}

    Q_INVOKABLE void aboutQt()
    {
        qApp->aboutQt();
    }

    Q_INVOKABLE QString sha256(QString textToHash)
    {
        QByteArray byteArray;
        byteArray.append(textToHash);
        return QString(QCryptographicHash::hash(byteArray, QCryptographicHash::Sha256).toHex());
    }

    Q_INVOKABLE QString md5(QString textToHash)
    {
        QByteArray byteArray;
        byteArray.append(textToHash);
        return QString(QCryptographicHash::hash(byteArray, QCryptographicHash::Md5).toHex());
    }

    static QString encryptAsSha256(QString textToHash)
    {
        QByteArray byteArray;
        byteArray.append(textToHash);
        return QString(QCryptographicHash::hash(byteArray, QCryptographicHash::Sha256).toHex());
    }

    static QString encryptAsMD5(QString textToHash)
    {
        QByteArray byteArray;
        byteArray.append(textToHash);
        return QString(QCryptographicHash::hash(byteArray, QCryptographicHash::Md5).toHex());
    }

    Q_INVOKABLE bool isValidEmail(QString email)
    {
        QRegExp emailRegex;
        emailRegex.setCaseSensitivity(Qt::CaseInsensitive);
        emailRegex.setPattern(R"(\b[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,4}\b)");

        return emailRegex.exactMatch(email);
    }

    Q_INVOKABLE QString humanFileSize(float bytes, bool si)
    {
        const float tresh = si ? 1000 : 1024;
        if(bytes < tresh) return QString::number(bytes) + " B";

        int u = -1;

        do
        {
            bytes /= tresh;
            ++u;
        } while(bytes >= tresh);

        return QString::number(round(bytes)) + " " + (si ? units1[u] : units2[u]);
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

