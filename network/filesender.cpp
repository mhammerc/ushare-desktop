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

   /* QObject::connect(&http, &HttpSender::finished, [&http]()
    {
        std::cout << http.getResponse().toStdString() << std::endl; //Will show the access link
    });*/

    QObject::connect(&http, &HttpSender::uploadProgress, [](qint64 bytesSent, qint64 bytesTotal)
    {
        if(bytesTotal == 0) return; //If the bytesTotal is 0, there is a problem and it is no possible. So we avoid the showing of false informations.
        std::cout << bytesSent << " bytes sent, for a total of " << bytesTotal << " bytes. "
                  << (float)bytesSent/(float)bytesTotal*100.0 << "%"
                  << std::endl;
    });

    QObject::connect(&http, &HttpSender::statusChanged, [](const HttpSender::Status &status)
    {
        if(status == HttpSender::Status::FILE_ERROR)
            std::cout << "Can't open the file. Aborted." << std::endl;
    });

    QObject::connect(&http, &HttpSender::error, [](QNetworkReply::NetworkError e)
    {
        std::cout << "Error occured. Code : " << e << std::endl;
    });

    uploadingWindow = new UploadingWindow();

    QObject::connect(uploadingWindow, &UploadingWindow::cancellationAsked, this, &FileSender::cancelUpload);

    QObject::connect(&http, &HttpSender::uploadProgress, [this](qint64 bytesSent, qint64 bytesTotal)
    {
        if(bytesTotal == 0) return;
        uploadingWindow->setProgress((float)bytesSent/(float)bytesTotal);
    });

    uploadFinishedConnection = QObject::connect(&http, &HttpSender::finished, [this]()
    {
        uploadingWindow->terminateUpload(http.getResponse());
        //http.exit();
        //http.deleteLater();
    });

    QFileInfo fileInfo(file.path);

    uploadingWindow->show();
    uploadingWindow->setBytesTotal(fileInfo.size());


    //Call run function to send the file
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

