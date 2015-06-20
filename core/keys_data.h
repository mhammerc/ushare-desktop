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

#ifndef KEYS_DATA_H
#define KEYS_DATA_H

enum class SettingsKeys : int {
    USERNAME = 0,
    PASSWORD,
    COPY_LINK_TO_CLIPBOARD, // Boolean
    OPEN_FILE_IN_BROWSER, // Boolean
    PLAY_SOUND_ON_SUCCESS_UPLOAD, // boolean
    IMAGE_FORMAT, // 0 -> JPEG or 1 -> PNG
    IMAGE_QUALITY, // From 0 to 100
    SAVE_IMAGE_ON_COMPUTER, // Boolean
    PATH_TO_SAVE_IMAGE_ON_COMPUTER, // String path
    SHOW_NOTIFICATION_WINDOW,
    SHOW_PROGRESS_WINDOW,
    ACCOUNT_KEY,
    PRIVATE_KEY,
    LANGUAGE,
    SHORTCUT_FULLSCREEN,
    SHORTCUT_AREASCREEN,
    SHORTCUT_NEWPASTE,
    SHORTCUT_SENDFILE,
    SHORTCUT_SENDCLIPBOARD
};

#endif // KEYS_DATA_H

