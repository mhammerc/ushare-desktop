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

#ifndef UPLIMG_H
#define UPLIMG_H

#include <QObject>
#include <QClipboard>
#include <QDesktopServices>
#include <QUrl>
#include <QPixmap>
#include <QColor>
#include <QTranslator>

#include "core/shared.h"

#include "core/systemtrayicon.h"
#include "core/screentaker.h"
#include "sounds/filesendedsound.h"
#include "file/filemanager.h"
#include "network/filesender.h"

#include "windows/mainwindow.h"
#include "windows/notificationwindow.h"
#include "windows/pastewindow.h"

#include "core/settings.h"

#include <iostream>

/* This link all modules between them */

class uShare : public QObject
{
    Q_OBJECT
public:
    explicit uShare(QObject *parent = 0);
    void start();

    SystemTrayIcon * getSystemTray();

private:
    void initModules();
    void linkConnections();

    SystemTrayIcon * systemTray;
    ScreenTaker * screenTaker;
    FileManager * fileManager;
    FileSender * fileSender;
    FileSendedSound fileSendedSound;

    MainWindow * mainWindow;
    PasteWindow pasteWindow;


signals:

public slots:
    void startCaptureSelectedScreenProccess();
    void captureSelectedScreenProccessCanceled();

    void makePaste();

    void autoSendFile(File);
};

#endif // UPLIMG_H
