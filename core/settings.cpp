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
         << "show_progress_window"
         << "account_key"
         << "private_key"
         << "language"
         << "fullscreen_shortcut"
         << "selectedareascreen_shortcut"
         << "newpaste_shortcut"
         << "sendfile_shortcut"
         << "sendclipboard_shortcut";

}

Settings::~Settings()
{

}

