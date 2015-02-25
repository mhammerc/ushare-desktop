#include "filesender.h"

FileSender::FileSender(QObject *parent) : QObject(parent)
{

}

FileSender::~FileSender()
{

}

void FileSender::autoSendFile(File file)
{
    http.setHost("http://uplmg.com/insert/upload", 80);
    http.setFile(file.path);
    http.setUplimgVersion("2.0");

    uploadingWindow = new UploadingWindow();

    QObject::connect(uploadingWindow, &UploadingWindow::cancellationAsked, this, &FileSender::cancelUpload);

    QObject::connect(&http, &HttpSender::uploadProgress, [this](qint64 bytesSent, qint64 bytesTotal)
    {
        if(bytesTotal == 0) return;
        uploadingWindow->setProgress((float)bytesSent/(float)bytesTotal);
    });

    uploadFinishedConnection = QObject::connect(&http, &HttpSender::finished, [this]()
    {
        QString response = http.getResponse();
        uploadingWindow->terminateUpload(response);
        emit uploadFinished(response);
    });

    QFileInfo fileInfo(file.path);

    uploadingWindow->show();
    uploadingWindow->setBytesTotal(fileInfo.size());

    // Call run function to send the file
    http.start();
}

void FileSender::cancelUpload()
{
    QObject::disconnect(uploadFinishedConnection);
    QObject::connect(&http, &HttpSender::finished, this, &FileSender::cancelFinished);

    http.abort();
}

void FileSender::cancelFinished()
{
    http.quit();

    uploadingWindow->deleteLater();
}

