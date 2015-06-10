#include "uploadingwindow.h"

UploadingWindow::UploadingWindow(QObject *parent) : QObject(parent)
{
    component = new QQmlComponent(&engine, QUrl::fromLocalFile("qml/upload_window/UploadWindow.qml"), this);

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
