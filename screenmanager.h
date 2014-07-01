#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H



#include <QApplication>
#include <QScreen>
#include <QGuiApplication>
#include <QPixmap>
#include <QStandardPaths>
#include <QString>
#include <QTime>
#include <QDate>
#include <QSettings>
#include <QLabel>
#include <QColor>
#include <QBitmap>
#include <QRgb>
#include <QObject>
#include <string>
#include "ftpupload.h"
#include "selectareaband.h"
#include "httppostupload.h"
#include <SFML/Network.hpp>

#include <memory>


//WARNING To delete
#include <iostream>


class SystemTrayIcon;

class ScreenManager : public QObject
{
    Q_OBJECT
public:
    ScreenManager(SystemTrayIcon * parent);
    ~ScreenManager();

    QString captureSelectedZone(const QString &pathToScreen);
    QString captureFullScreen(const QString &pathToScreen);

    bool sendFileTroughHTTP(const QString &pathToFile);
    bool sendFileTroughFTP(const QString &pathToFile);

protected:
    QSettings settings;
    const QString choosedMethodSettingName;

    //FTP
    const QString FTPHostSettingName;
    const QString FTPPortSettingName;
    const QString FTPUsernameSettingName;
    const QString FTPPasswordSettingName;
    const QString FTPBasePathSettingName;

    //HTTP
    const QString HTTPHostSettingName;
    const QString HTTPPortSettingName;
    const QString HTTPFileFieldNameSettingName;

    const int darkenFactor;

    bool isFileSended;

    QPixmap darkenPicture(const QPixmap &picture);

    SystemTrayIcon * parent;

    QPixmap originalScreenshot;
    QString pathToFile;

public slots:
    void areaPictureTaken(QRect);
    bool autoSendFile(const QString &pathToFile);
    void fileSendedTroughHTTP();


signals:
    void canSend();

};

#endif // SCREENMANAGER_H
