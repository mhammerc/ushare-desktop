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

#include <QxtCore/Qxt>
#include <QxtWidgets/QxtGlobalShortcut>

#include "configuration/configurationwindows.h"
#include "screenmanager.h"
#include "shared.h"

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
    ScreenManager * screenManager;

    QMenu * systemTrayMenu;
    QAction * takeScreen;
    QAction * takeSelectedScreen;
    QAction * uploadFile;
    QAction * uploadClipboard;
    QAction * showConfiguration;
    QAction * quit;

    void setUpContextMenu();
    QString getNewFileName(Uplimg::ImageFormat ending);
    QString getNewFileName(QString ending);
    QString getFileTempPath(const QString &screenName);
    QString getUploadedFileURL(const QString &fileName);
    void firstStart();

    QSound * fileSendedSound;

    QxtGlobalShortcut * takeFullScreenShortcut;
    QxtGlobalShortcut * takeSelectedAreaScreenShortcut;
    QxtGlobalShortcut * uploadFileShortcut;
    QxtGlobalShortcut * uploadClipboardShortcut;

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

    void openLastUrl();
    void copyLastUrlToClipboard();

    void activatedTrigerred(QSystemTrayIcon::ActivationReason);

    void takeFullScreenShortcutChanged(QString);
    void takeSelectedAreaScreenShortcutChanged(QString);
    void uploadFileShortcutChanged(QString);
    void uploadClipboardShortcutChanged(QString);
};

#endif // SYSTEMTRAYICON_H
