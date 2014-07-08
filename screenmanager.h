#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#include <iostream>
#include <memory>

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

#include <SFML/Network.hpp>

#include "selectareaband.h"
#include "uploadMethod/ftpupload.h"
#include "uploadMethod/httppostupload.h"

#include "shared.h"

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
    SystemTrayIcon * parent;
    QSettings settings;

    const int darkenFactor;
    bool isFileSended;

    QPixmap darkenPicture(const QPixmap &picture);

    QPixmap originalScreenshot;
    QString pathToFile;

    SelectAreaBand * fullScreenPicture;
    QScreen * screen;

public slots:
    void areaPictureTaken(QRect);
    bool autoSendFile(const QString &pathToFile);
    void fileSendedTroughHTTP();


signals:
    void canSend();

};

#endif // SCREENMANAGER_H
