#ifndef QMLSETTINGS_H
#define QMLSETTINGS_H

#include <QObject>
#include <QSettings>

#include "core/shared.h"

class QmlSettings : public QSettings
{
    Q_OBJECT
public:
    QmlSettings(QObject *parent = 0);
    virtual ~QmlSettings();

    Q_INVOKABLE void setValue(const QString &key, const QVariant &value);

    Q_INVOKABLE void setValueIfNotSet(const QString &key, const QVariant &value);

    Q_INVOKABLE QVariant value(const QString &key, const QVariant &defaultValue);

    Q_INVOKABLE bool boolValue(const QString &key, const bool defaultValue);

    Q_PROPERTY(QString uploadUrl READ uploadUrl CONSTANT FINAL)

    Q_PROPERTY(QString deleteUrl READ deleteUrl CONSTANT FINAL)

    Q_PROPERTY(QString editPasswordUrl READ editPasswordUrl CONSTANT FINAL)

    Q_PROPERTY(QString appVersion READ appVersion CONSTANT FINAL)

    Q_PROPERTY(int globalPort READ globalPort CONSTANT FINAL)

    Q_PROPERTY(QString authUrl READ authUrl CONSTANT FINAL)

    Q_PROPERTY(QString registerUrl READ registerUrl CONSTANT FINAL)

    Q_PROPERTY(QString silentViewUrl READ silentViewUrl CONSTANT FINAL)

    Q_PROPERTY(QString updateInfoUrl READ updateInfoUrl CONSTANT FINAL)

    Q_PROPERTY(QString domainName READ domainName CONSTANT FINAL)

    Q_PROPERTY(QString os READ os CONSTANT FINAL)

    Q_PROPERTY(QString arch READ arch CONSTANT FINAL)

    const QString uploadUrl()
    {
        return Shared::uploadUrl;
    }

    const QString deleteUrl()
    {
        return Shared::deleteUrl;
    }

    const QString editPasswordUrl()
    {
        return Shared::editPasswordUrl;
    }

    const QString appVersion()
    {
        return Shared::appVersion;
    }

    int globalPort()
    {
        return Shared::globalPort;
    }

    const QString authUrl()
    {
        return Shared::authUrl;
    }

    const QString registerUrl()
    {
        return Shared::registerUrl;
    }

    const QString silentViewUrl()
    {
        return Shared::silentViewUrl;
    }

    const QString updateInfoUrl()
    {
        return Shared::updateInfoUrl;
    }

    const QString domainName()
    {
        return Shared::domainName;
    }

    const QString os()
    {
#ifdef __linux__
        return "linux";
#elif _WIN32
        return "windows";
#elif __APPLE__
        return "macosx";
#endif
    }

    const QString arch()
    {
#ifdef __amd64__
        return "x64";
#elif _M_X64
        return "x64";
#elif __i386
        return "x32";
#elif _M_IX86
        return "x32";
#elif _X86_
        return "x32";
#endif
    }
};

#endif // QMLSETTINGS_H
