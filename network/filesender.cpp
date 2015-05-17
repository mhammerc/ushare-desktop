#include "filesender.h"

FileSender::FileSender(QObject *parent) : QObject(parent)
{

}

FileSender::~FileSender()
{

}

void FileSender::autoSendFile(File file)
{
    http.setHost(Shared::uploadUrl, Shared::globalPort);
    http.setFile(file.path);

    if(Settings::entry(SettingsKeys::SHOW_PROGRESS_WINDOW).toBool())
    {
        // If the user want the progress window
        uploadingWindow = new UploadingWindow();

        QObject::connect(uploadingWindow, &UploadingWindow::cancellationAsked, this, &FileSender::cancelUpload);

        QObject::connect(&http, &HttpSender::uploadProgress, [this](qint64 bytesSent, qint64 bytesTotal)
        {
            if(bytesTotal == 0) return;
            uploadingWindow->setProgress((float)bytesSent/(float)bytesTotal);
        });

        uploadFinishedConnection = QObject::connect(&http, &HttpSender::finished, [this]()
        {
            uploadingWindow->deleteLater();

            QString response = http.getResponse();
            emit uploadFinished(response);
        });

        QFileInfo fileInfo(file.path);

        uploadingWindow->setBytesTotal(fileInfo.size());
        uploadingWindow->show();
    }
    else
    {
        uploadFinishedConnection = QObject::connect(&http, &HttpSender::finished, [this]()
        {
            QString response = http.getResponse();
            emit uploadFinished(response);
        });
    }

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

