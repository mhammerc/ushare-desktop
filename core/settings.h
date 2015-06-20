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

#ifndef SETTINGS_H
#define SETTINGS_H

#include <QSettings>
#include <QString>
#include <QStringList>
#include <QVariant>

#include "keys_data.h"

#include <QDebug>


class Settings : public QSettings
{
public:
    /* Call it before first use to avoid memory leaks. Just give a parent */
    static void init(QObject * parent)
    {
        get(parent);
    }

    Q_INVOKABLE static void setEntry(const SettingsKeys key, const QVariant &value);

    Q_INVOKABLE static const QVariant entry(const SettingsKeys key, const QVariant &defaultValue = QVariant());

    Settings(QObject * parent = 0);
    ~Settings();

private:
    static Settings * get(QObject * parent = 0)
    {
        static Settings * s;
        if(!s) s = new Settings(parent);
        return s;
    }

    QStringList keys;
    const QString getStringKey(const SettingsKeys key);
};

#endif // SETTINGS_H
