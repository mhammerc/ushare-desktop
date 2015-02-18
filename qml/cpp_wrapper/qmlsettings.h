#ifndef QMLSETTINGS_H
#define QMLSETTINGS_H

#include <QObject>
#include <QSettings>

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
};

#endif // QMLSETTINGS_H
