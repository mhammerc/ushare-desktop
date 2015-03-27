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

    Q_PROPERTY(int uploadPort READ uploadPort CONSTANT FINAL)

    Q_PROPERTY(QString appVersion READ appVersion CONSTANT FINAL)

    Q_PROPERTY(int globalPort READ globalPort CONSTANT FINAL)

    Q_PROPERTY(QString authUrl READ authUrl CONSTANT FINAL)

    Q_PROPERTY(QString registerUrl READ registerUrl CONSTANT FINAL)

    Q_PROPERTY(QString wsUrl READ wsUrl CONSTANT FINAL)

    Q_PROPERTY(QString silentViewUrl READ silentViewUrl CONSTANT FINAL)

    Q_PROPERTY(QString domainName READ domainName CONSTANT FINAL)

    const QString uploadUrl()
    {
        return Shared::uploadUrl;
    }

    int uploadPort()
    {
        return Shared::uploadPort;
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

    const QString wsUrl()
    {
        return Shared::wsUrl;
    }

    const QString silentViewUrl()
    {
        return Shared::silentViewUrl;
    }

    const QString domainName()
    {
        return Shared::domainName;
    }
};

#endif // QMLSETTINGS_H
