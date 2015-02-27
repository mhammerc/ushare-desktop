#include "uploadingwindow.h"

UploadingWindow::UploadingWindow(QObject *parent) : QObject(parent)
{
    component = new QQmlComponent(&engine, QUrl::fromLocalFile("qml/upload_window/UploadWindow.qml"), this);
    qDebug() << component->errorString();
    window = component->create();

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
