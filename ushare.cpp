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

#include "ushare.h"

uShare::uShare(QObject *parent) :
    QObject(parent),
    pasteWindow(this)
{
}

void uShare::start()
{
    initModules();
    linkConnections();

    // and then..
    systemTray->setVisible(true);
}

SystemTrayIcon * uShare::getSystemTray()
{
    return systemTray;
}

void uShare::initModules()
{
    systemTray = new SystemTrayIcon(this);

    mainWindow = new MainWindow(systemTray, this);

    screenTaker = new ScreenTaker(this);

    fileManager = new FileManager(this);
}

void uShare::linkConnections()
{
    /* Connection to the system tray */
    QObject::connect(systemTray, &SystemTrayIcon::captureFullScreenAsked, [this]()
    {
        fileManager->screenTook(screenTaker->captureFullScreen());
    });

    QObject::connect(systemTray, &SystemTrayIcon::openLastFile, [this]()
    {
        QDesktopServices::openUrl(QUrl(lastFileLink));
    });

    QObject::connect(systemTray, &SystemTrayIcon::captureSelectedScreenAsked, this, &uShare::startCaptureSelectedScreenProccess);
    QObject::connect(systemTray, &SystemTrayIcon::sendFileAsked, fileManager, &FileManager::chooseFile);
    QObject::connect(systemTray, &SystemTrayIcon::sendClipboardAsked, fileManager, &FileManager::sendClipboard);
    QObject::connect(systemTray, &SystemTrayIcon::makePasteAsked, this, &uShare::makePaste);
    QObject::connect(systemTray, &SystemTrayIcon::openUplimgAsked, mainWindow, &MainWindow::show);

    /* Connections from the screen taker */
    QObject::connect(screenTaker, &ScreenTaker::captureSelectedZoneFinished, fileManager, &FileManager::screenTook); /* Send the screen took to the file manager */
    QObject::connect(screenTaker, &ScreenTaker::captureSelectedZoneCanceled, this, &uShare::captureSelectedScreenProccessCanceled);

    /* Connections from the file manager */
    QObject::connect(fileManager, &FileManager::fileReadyToBeSent, this, &uShare::autoSendFile);

    /* Connections from paste manager */
    QObject::connect(&pasteWindow, &PasteWindow::pasteReady, fileManager, &FileManager::sendDatas);
}

void uShare::startCaptureSelectedScreenProccess()
{
    screenTaker->captureSelectedZone(QColor(255,0,0));
}

void uShare::captureSelectedScreenProccessCanceled()
{
    /* return in idle state */
}

void uShare::makePaste()
{
    pasteWindow.newPaste();
}

void uShare::autoSendFile(File file)
{
    FileSender * fileSender = new FileSender(this);

    QObject::connect(fileSender, &FileSender::uploadFinished, [this](QString response)
    {
        if(Settings::entry(SettingsKeys::COPY_LINK_TO_CLIPBOARD).toBool())
            // If the user want to copy the response inside his clipboard
            QApplication::clipboard()->setText(response);

        if(Settings::entry(SettingsKeys::OPEN_FILE_IN_BROWSER).toBool())
            // If the user want to automatically open the file in browser
            QDesktopServices::openUrl(QUrl(response));

        if(Settings::entry(SettingsKeys::PLAY_SOUND_ON_SUCCESS_UPLOAD).toBool())
            // If the user want to play a sound on upload success
            fileSendedSound.play();

        if(Settings::entry(SettingsKeys::SHOW_NOTIFICATION_WINDOW).toBool())
        { // If the user want a notification window

            QString message = tr("Your file is uploaded!\nThe link is ") + response;

            if(Settings::entry(SettingsKeys::USE_WINDOWS10_NATIVE_NOTIFICATIONS).toBool())
            {
                systemTray->showMessage("uShare", message, QSystemTrayIcon::NoIcon);
                return;
            }

            NotificationWindow * notif = new NotificationWindow(tr("Congratulations!"), message, response);
            notif->show();
        }

        lastFileLink = response;
    });

    fileSender->autoSendFile(file);
}
