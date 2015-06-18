#include "mainwindow.h"

MainWindow::MainWindow(SystemTrayIcon *systemTrayIcon, QObject *parent) : QObject(parent)
{
    component = new QQmlComponent(&engine, QUrl("qrc:/qml/main_window/main.qml"), this);

    /* create the context to set Settings before the creation */
    context = new QQmlContext(&engine);

    UShareOnline * uShareOnline = new UShareOnline(this);
    context->setContextProperty("uShareOnline", uShareOnline);

    QmlSettings * settings = new QmlSettings(this);
    context->setContextProperty("Settings", settings);

    Clipboard * cb = new Clipboard(this);
    context->setContextProperty("Clipboard", cb);

    QmlDesktop * dk = new QmlDesktop(this);
    context->setContextProperty("Desktop", dk);

    Shortcuts * s = new Shortcuts(systemTrayIcon, this);
    context->setContextProperty("Shortcuts", s);

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

