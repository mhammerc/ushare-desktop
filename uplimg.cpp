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
    QObject::connect(systemTray, &SystemTrayIcon::openUplimgAsked, mainWindow, &MainWindow::show);

    /* Connections from the screen taker */
    QObject::connect(screenTaker, &ScreenTaker::captureSelectedZoneFinished, fileManager, &FileManager::screenTook); /* Send the screen took to the file manager */
    QObject::connect(screenTaker, &ScreenTaker::captureSelectedZoneCanceled, this, &Uplimg::captureSelectedScreenProccessCanceled);

    /* Connections from the file manager */
    QObject::connect(fileManager, &FileManager::fileReadyToBeSent, this, &Uplimg::autoSendFile);
}

void Uplimg::startCaptureFullScreenProccess()
{
    std::cout << "ok" << std::endl;
}

void Uplimg::startCaptureSelectedScreenProccess()
{
    screenTaker->captureSelectedZone(QColor(255,0,0));
}

void Uplimg::captureSelectedScreenProccessCanceled()
{
    /* return in idle state */
    std::cout << "canceled" << std::endl;
}

void Uplimg::autoSendFile(File file)
{
    FileSender * fileSender = new FileSender(this);
    fileSender->autoSendFile(file);
}
