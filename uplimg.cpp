#include "uplimg.h"

Uplimg::Uplimg(QObject *parent) : QObject(parent)
{

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
}

void Uplimg::linkConnections()
{
    /* Connection to the system tray */
    QObject::connect(systemTray, &SystemTrayIcon::captureFullScreenAsked, this, &Uplimg::startCaptureFullScreenProccess);
    QObject::connect(systemTray, &SystemTrayIcon::captureSelectedScreenAsked, this, &Uplimg::startCaptureSelectedScreenProccess);
    QObject::connect(systemTray, &SystemTrayIcon::openUplimgAsked, mainWindow, &MainWindow::show);

    /* Connections from the screen taker */
    QObject::connect(screenTaker, &ScreenTaker::captureSelectedZoneFinished, this, &Uplimg::captureSelectedScreenProccessFinished);
    QObject::connect(screenTaker, &ScreenTaker::captureSelectedZoneCanceled, this, &Uplimg::captureSelectedScreenProccessCanceled);
}

void Uplimg::startCaptureFullScreenProccess()
{
    std::cout << "ok" << std::endl;
}

void Uplimg::startCaptureSelectedScreenProccess()
{
    screenTaker->captureSelectedZone(QColor(255,0,0));
}

void Uplimg::captureSelectedScreenProccessFinished(QPixmap picture)
{
    /* transmit the file to the sender */
    std::cout << "finished" << std::endl;
}

void Uplimg::captureSelectedScreenProccessCanceled()
{
    /* return in idle state */
    std::cout << "canceled" << std::endl;
}
