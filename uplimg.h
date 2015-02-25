#ifndef UPLIMG_H
#define UPLIMG_H

#include <QObject>
#include <QClipboard>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include <QColor>

#include "core/systemtrayicon.h"
#include "core/screentaker.h"
#include "sounds/filesendedsound.h"
#include "file/filemanager.h"
#include "network/filesender.h"
#include "windows/mainwindow.h"

#include "core/settings.h"

#include <iostream>

/* This link all modules between them */

class Uplimg : public QObject
{
    Q_OBJECT
public:
    explicit Uplimg(QObject *parent = 0);
    ~Uplimg();
    void start();

    SystemTrayIcon *getSystemTray();

private:
    void initModules();
    void linkConnections();

    SystemTrayIcon * systemTray;
    ScreenTaker * screenTaker;
    FileManager * fileManager;
    FileSender * fileSender;
    MainWindow * mainWindow;
    FileSendedSound fileSendedSound;


signals:

public slots:
    void startCaptureSelectedScreenProccess();
    void captureSelectedScreenProccessCanceled();

    void autoSendFile(File);
};

#endif // UPLIMG_H
