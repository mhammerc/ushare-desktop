#include "uplimg.h"

Uplimg::Uplimg(QObject *parent) : QObject(parent)
{
    Settings::init(this);
}

Uplimg::~Uplimg()
{

}

void Uplimg::start()
{
    initModules();
    linkConnections();

    // and then..
    systemTray->show();
}

SystemTrayIcon * Uplimg::getSystemTray()
{
    return systemTray;
}

void Uplimg::initModules()
{
    mainWindow = new MainWindow(this);

    systemTray = new SystemTrayIcon(this);

    screenTaker = new ScreenTaker(this);

    fileManager = new FileManager(this);
}

void Uplimg::linkConnections()
{
    /* Connection to the system tray */
    QObject::connect(systemTray, &SystemTrayIcon::captureFullScreenAsked, [this](){fileManager->screenTook(screenTaker->captureFullScreen());});
    QObject::connect(systemTray, &SystemTrayIcon::captureSelectedScreenAsked, this, &Uplimg::startCaptureSelectedScreenProccess);
    QObject::connect(systemTray, &SystemTrayIcon::sendFileAsked, fileManager, &FileManager::chooseFile);
    QObject::connect(systemTray, &SystemTrayIcon::openUplimgAsked, mainWindow, &MainWindow::show);

    /* Connections from the screen taker */
    QObject::connect(screenTaker, &ScreenTaker::captureSelectedZoneFinished, fileManager, &FileManager::screenTook); /* Send the screen took to the file manager */
    QObject::connect(screenTaker, &ScreenTaker::captureSelectedZoneCanceled, this, &Uplimg::captureSelectedScreenProccessCanceled);

    /* Connections from the file manager */
    QObject::connect(fileManager, &FileManager::fileReadyToBeSent, this, &Uplimg::autoSendFile);
}

void Uplimg::startCaptureSelectedScreenProccess()
{
    screenTaker->captureSelectedZone(QColor(255,0,0));
}

void Uplimg::captureSelectedScreenProccessCanceled()
{
    /* return in idle state */
}

void Uplimg::autoSendFile(File file)
{
    FileSender * fileSender = new FileSender(this);

    QObject::connect(fileSender, &FileSender::uploadFinished, [this](QString response){

        if(Settings::entry(SettingsKeys::COPY_LINK_TO_CLIPBOARD).toBool())
            // If the user want to copy the response inside his clipboard
            QApplication::clipboard()->setText(response);

        if(Settings::entry(SettingsKeys::OPEN_FILE_IN_BROWSER).toBool())
            // If the user want to automatically open the file in browser
            QDesktopServices::openUrl(QUrl(response));

        if(Settings::entry(SettingsKeys::PLAY_SOUND_ON_SUCCESS_UPLOAD).toBool())
            // If the user want to play a sound on upload success
            fileSendedSound.play();
    });

    fileSender->autoSendFile(file);
}
