/**
 * This file (c) by : - Martin Hammerchmidt alias Imote
 *
 * This file is licensed under a
 * GNU GENERAL PUBLIC LICENSE V3.0
 *
 * See the LICENSE file to learn more.
 *
 * If you have contributed to this file, add your name to authors list.
*/

#include "qmlsettings.h"

QVariant QmlSettings::value(const QString &key, const QVariant &defaultValue = QVariant())
{
    return QSettings::value(key, defaultValue);
}

bool QmlSettings::boolValue(const QString &key, bool defaultValue)
{
    return QSettings::value(key, defaultValue).toBool();
}

void QmlSettings::setStartOnStartup(bool enabled)
{
#ifdef _WIN32
    QSettings s("HKEY_CURRENT_USER\\SOFTWARE\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);

    if(enabled)
    {
        QString exePath = "\"" + qApp->applicationFilePath() + "\"";
        exePath.replace("/", "\\");
        s.setValue("uShare", exePath);
    }
    else
    {
        s.remove("uShare");
    }
#endif
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

