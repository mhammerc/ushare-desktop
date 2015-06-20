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

