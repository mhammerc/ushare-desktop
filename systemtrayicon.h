#ifndef SYSTEMTRAYICON_H
#define SYSTEMTRAYICON_H

#include <fstream>

#include <QApplication>
#include <QMenu>
#include <QAction>
#include <QList>
#include <QSystemTrayIcon>
#include <QClipboard>
#include <QIcon>
#include <QShortcut>
#include <QFileDialog>
#include <QString>
#include <QMessageBox>
#include <QFileInfo>
#include <QSound>
#include <QSoundEffect>
#include <QAudioOutput>
#include <QDesktopServices>
#include <QUrl>
#include <QVariant>
#include <QStandardPaths>

#include <QxtCore/Qxt>
#include <QxtWidgets/QxtGlobalShortcut>

#include "configuration/configurationwindows.h"
#include "screenmanager.h"
#include "FileDialog.h"
#include "shared.h"

class SystemTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit SystemTrayIcon(QObject *qobject = 0);
    ~SystemTrayIcon();
    Uplimg::UploadMethod getUploadMethod() const;
    Uplimg::ImageFormat getImageFormat() const;
    int getImageQuality() const;

    QUrl lastUrl;

protected:
    const QString applicationName;
    const QString HTTPWebPathSettingName;
    const QString FTPWebPathSettingName;
    const QString runOnStartupSettingName;
    const QString choosedMethodSettingName;
    const QString showNotificationsSettingName;
    const QString playSoundSettingName;
    const QString copyToClipboardSettingName;
    const QString takeFullScrenShortcutSettingName;
    const QString takeSelectedAreaScreenShortcutSettingName;
    const QString uploadFileShortcutSettingName;
    const QString uploadClipboardShortcutSettingName;
    const QString autoOpenToBrowserSettingName;
    const QString imageFormatSettingName;
    const QString imageQualitySettingName;
    const QString localSaveSettingName;
    const QString localSavePathSettingName;
    const QString linkFromSettingName;

    QSettings settings;

    ConfigurationWindows * configurationWindows;
    ScreenManager * screenManager;

    QMenu * systemTrayMenu;
    QAction * takeScreen;
    QAction * takeSelectedScreen;
    QAction * uploadFile;
    QAction * uploadClipboard;
    QAction * showConfiguration;
    QAction * quit;

    QShortcut * shortcut;

    void setUpContextMenu();
    QString getNewFileName(Uplimg::ImageFormat ending);
    QString getNewFileName(QString ending);
    QString getFileTempPath(const QString &screenName);
    QString getUploadedFileURL(const QString &fileName);
    void firstStart();

    QSound * fileSendedSound;

    QxtGlobalShortcut * takeFullScrenShortcut;
    QxtGlobalShortcut * takeSelectedAreaScreenShortcut;
    QxtGlobalShortcut * uploadFileShortcut;
    QxtGlobalShortcut * uploadClipboardShortcut;

    QKeySequence takeFullScreenKeySequence;
    QKeySequence takeSelectedAreaKeySequence;
    QKeySequence uploadFileKeySequence;
    QKeySequence uploadClipboardKeySequence;

    //Temp
    QString fileName;
    QString pathToFile;

signals:

public slots :
    void showWindowConfigurationTriggered();
    void takeFullScrenTriggered();
    void takeSelectedAreaScreenTriggered();
    void uploadSelectedFileTriggered();
    void uploadClipboardTriggered();
    void fileSended(QString fileName);

    void sendSelectedArea();

    void throwErrorAlert(const QString &text);
    void throwErrorAlert(const Uplimg::ErrorList &error);

    void enableEasterEgg();

    void openLastUrl();

    void activatedTrigerred(QSystemTrayIcon::ActivationReason);
};

#endif // SYSTEMTRAYICON_H
