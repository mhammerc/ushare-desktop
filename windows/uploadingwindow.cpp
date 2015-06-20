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

#include "uploadingwindow.h"

UploadingWindow::UploadingWindow(QObject *parent) : QObject(parent)
{
    component = new QQmlComponent(&engine, QUrl("qrc:/qml/upload_window/UploadWindow.qml"), this);

    context = new QQmlContext(&engine);

    QmlDesktop * desktop = new QmlDesktop(this);
    context->setContextProperty("Desktop", desktop);

    window = component->create(context);
    qDebug() << component->errorString();

    QObject::connect(window, SIGNAL(cancellationAsked()), this, SIGNAL(cancellationAsked()));
}

UploadingWindow::~UploadingWindow()
{
    window->deleteLater();
}

void UploadingWindow::show()
{
    window->setProperty("visible", true);
}

void UploadingWindow::hide()
{
    window->setProperty("visible", false);
}

void UploadingWindow::setProgress(float progress)
{
    window->setProperty("progress", progress);
}

void UploadingWindow::setBytesTotal(qint64 total)
{
    window->setProperty("bytesTotal", total);
}
