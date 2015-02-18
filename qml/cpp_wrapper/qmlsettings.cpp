#include "qmlsettings.h"

QVariant QmlSettings::value(const QString &key, const QVariant &defaultValue = QVariant())
{
    return QSettings::value(key, defaultValue);
}

bool QmlSettings::boolValue(const QString &key, bool defaultValue)
{
    return QSettings::value(key, defaultValue).toBool();
}

void QmlSettings::setValue(const QString &key, const QVariant &value)
{
    QSettings::setValue(key, value);
}

void QmlSettings::setValueIfNotSet(const QString &key, const QVariant &value)
{
    if( !QSettings::contains(key) )
        QSettings::setValue(key, value);

}

QmlSettings::QmlSettings(QObject * parent) : QSettings(parent)
{

}

QmlSettings::~QmlSettings()
{

}

