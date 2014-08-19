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
#include "paste/pastewindow.h"
#include "paste/pastecontent.h"

#include "shared.h"

class SystemTrayIcon;

class FileManager : public QObject
{
    Q_OBJECT
public:
    FileManager(SystemTrayIcon * parent);
    ~FileManager();

    QString captureSelectedZone(const QString &pathToScreen);
    QString captureFullScreen(const QString &pathToScreen);
    void startPastMode();

    bool sendFileTroughHTTP(const QString &pathToFile);
    bool sendFileTroughFTP(const QString &pathToFile);
    bool sendFileTroughUplimgWeb(const QString &pathToFile);

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

    PasteWindow * paste;

public slots:
    void areaPictureTaken(QRect);
    void areaPictureCanceled();
    bool autoSendFile(const QString &pathToFile);
    void fileSendedTroughHTTP();

    void pasteReady(PasteContent const &paste);


signals:
    void canSend();

};

#endif // SCREENMANAGER_H
