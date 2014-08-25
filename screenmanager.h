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
#include "containers/pastecontent.h"

#include "shared.h"

class SystemTrayIcon;

class FileManager : public QObject
{
    Q_OBJECT
public:
    FileManager(SystemTrayIcon * parent);
    ~FileManager();

    File captureSelectedZone(const File &file);
    File captureFullScreen(File &file);
    void startPastMode();

    void sendFileTroughHTTP(const File &file);
    void sendFileTroughFTP(const File &file);
    void sendFileTroughUplimgWeb(const File &file);

protected:
    SystemTrayIcon * parent;
    QSettings settings;

    const int darkenFactor;

    QPixmap darkenPicture(const QPixmap &picture);

    QPixmap originalScreenshot;
    File lastFile;

    SelectAreaBand * fullScreenPicture;
    QScreen * screen;

    PasteWindow * paste;

    HTTPPostUpload * http;
    FTPUpload * ftp;

public slots:
    void areaPictureTaken(QRect);
    void areaPictureCanceled();
    void autoSendFile(const File &file);
    void fileSendedTroughHTTP();
    void fileSendedTroughFTP();

    void pasteReady(PasteContent const &paste);


signals:
    void canSend();

};

#endif // SCREENMANAGER_H
