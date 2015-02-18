#include "settings.h"

void Settings::setEntry(const SettingsKeys key, const QVariant &value)
{
    Settings * s = get();
    QString stringKey = s->getStringKey(key);
    s->setValue(stringKey, value);
}

const QVariant Settings::entry(const SettingsKeys key, const QVariant &defaultValue)
{
    Settings * s = get();
    QString stringKey = s->getStringKey(key);
    return s->value(stringKey, defaultValue);
}

const QString Settings::getStringKey(const SettingsKeys key)
{

    return keys.at((int)key);
}

Settings::Settings(QObject *parent) : QSettings(parent)
{
    keys << "username"
         << "password";

}

Settings::~Settings()
{

}

