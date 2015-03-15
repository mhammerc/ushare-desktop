#include "mainwindow.h"

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{
    component = new QQmlComponent(&engine, QUrl::fromLocalFile("qml/main_window/main.qml"), this);

    /* create the context to set Settings before the creation */
    context = new QQmlContext(&engine);

    QmlSettings * settings = new QmlSettings(this);
    context->setContextProperty("Settings", settings);

    PlatformDetails * pd = new PlatformDetails(this);
    context->setContextProperty("PlatformDetails", pd);

    Clipboard * cb = new Clipboard(this);
    context->setContextProperty("Clipboard", cb);

    QmlDesktop * dk = new QmlDesktop(this);
    context->setContextProperty("Desktop", dk);

    window = component->create(context);
    qDebug() << component->errorString();

    window->setProperty("visible", true);

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

