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
    SHOW_PROGRESS_WINDOW
};

#endif // KEYS_DATA_H

