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
}

void Uplimg::linkConnections()
{
    QObject::connect(systemTray, &SystemTrayIcon::openUplimgAsked, mainWindow, &MainWindow::show);
}

