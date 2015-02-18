#include "mainwindow.h"

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{
    component = new QQmlComponent(&engine, QUrl::fromLocalFile("/home/imote/Development/Uplimg/qml/mainWindow.qml"), this);

    /* create the context to set Settings before the creation */
    context = new QQmlContext(&engine);

    QmlSettings * settings = new QmlSettings();
    context->setContextProperty("Settings", settings);

    window = component->create(context);

}

MainWindow::~MainWindow()
{

}

void MainWindow::show()
{
    window->setProperty("visible", true);
}

void MainWindow::hide()
{
    window->setProperty("visible", false);
}

