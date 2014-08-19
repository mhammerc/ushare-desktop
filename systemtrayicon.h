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
#include <QTimer>
#include <QDir>
#include "shared.h"

#include "configuration/configurationwindows.h"
#include "filesendedsound.h"
#include "screenmanager.h"

#include <qxtglobal.h>
#include <QxtWidgets/QxtGlobalShortcut>

#ifdef _WIN32
#include <shortcut/shortcutmanager_win.h>
#endif


class SystemTrayIcon : public QSystemTrayIcon
{
    Q_OBJECT
public:
    explicit SystemTrayIcon(QObject *qobject = 0);
    ~SystemTrayIcon();

    QUrl lastUrl;
    QString receivedMessage;

protected:
    QSettings settings;

    ConfigurationWindows * configurationWindow;
    FileManager * screenManager;

    QMenu * systemTrayMenu;
    QAction * takeScreen;
    QAction * takeSelectedScreen;
    QAction * sendPaste;
    QAction * uploadFile;
    QAction * uploadClipboard;
    QAction * showConfiguration;
    QAction * quit;

    void setUpContextMenu();
    void firstStart();

    FileSendedSound fileSendedSound;

    ShortcutManager * takeFullScreenShortcut;
    ShortcutManager * takeSelectedAreaScreenShortcut;
    ShortcutManager * uploadFileShortcut;
    ShortcutManager * uploadClipboardShortcut;

    QKeySequence takeFullScreenKeySequence;
    QKeySequence takeSelectedAreaKeySequence;
    QKeySequence uploadFileKeySequence;
    QKeySequence uploadClipboardKeySequence;

    QTimer * iconTimer;

    //Temp
    QString fileName;
    QString pathToFile;
    bool actionBeing;

    bool lastUploadedFileSeparatorInserted;
    QAction * lastUploadedFileSeparator;
    short lastUploadedFileCounter;


signals:

public slots :
    void disableHotkeys();
    void enableHotkeys();

    void showWindowConfigurationTriggered();
    void takeFullScrenTriggered();
    void takeSelectedAreaScreenTriggered();
    void sendPasteTriggered();
    void uploadSelectedFileTriggered();
    void uploadClipboardTriggered();
    void fileSended(QString fileName);
    void lastActionFinished();
    void newActionStarted();
    void setWaitingIcon();
    void addUploadedFileInContextMenu();

    void sendSelectedArea();

    void throwErrorAlert(const QString &text);
    void throwErrorAlert(const Uplimg::ErrorList &error);

    void enableEasterEgg();

    void iconActivated(QSystemTrayIcon::ActivationReason);

    void takeFullScreenShortcutChanged(QString);
    void takeSelectedAreaScreenShortcutChanged(QString);
    void uploadFileShortcutChanged(QString);
    void uploadClipboardShortcutChanged(QString);

    void openLastUrl();
    void copyLastUrlToClipboard();
};

#endif // SYSTEMTRAYICON_H
