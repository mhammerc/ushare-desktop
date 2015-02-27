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
         << "password"
         << "copy_link_to_clipboard"
         << "open_file_in_browser"
         << "play_sound"
         << "picture/format"
         << "picture/quality"
         << "picture/save_on_computer"
         << "picture/save_path"
         << "show_notification_window"
         << "show_progress_window";

}

Settings::~Settings()
{

}

