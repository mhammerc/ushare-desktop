#include "httpsender.h"

HttpSender::HttpSender(){}

HttpSender::Status HttpSender::sendFile()
{
    QMimeDatabase mimeDatabase;

    /* We include all the file in part of the request */
    file = new QFile(pathToFile);
    QMimeType fileMimeType = mimeDatabase.mimeTypeForFile(pathToFile);

    if(!file->open(QIODevice::ReadOnly)) return HttpSender::FILE_ERROR;

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"file\"; filename=\"" + file->fileName() + "\""));
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, fileMimeType.name());
    filePart.setBodyDevice(file);

    /* Now we include user informations */
    QHttpPart accountKeyPart;
    accountKeyPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"accountkey\""));
    accountKeyPart.setBody(Settings::entry(SettingsKeys::ACCOUNT_KEY).toString().toStdString().c_str());

    QHttpPart privateKeyPart;
    privateKeyPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"privatekey\""));
    privateKeyPart.setBody(Settings::entry(SettingsKeys::PRIVATE_KEY).toString().toStdString().c_str());

    QHttpPart version;
    version.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"source\""));
    version.setBody(Shared::appVersion.toStdString().c_str());

    container = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    container->append(filePart);
    container->append(accountKeyPart);
    container->append(privateKeyPart);
    container->append(version);

    QNetworkRequest request;
    request.setUrl(url);

    manager = new QNetworkAccessManager();
    reply = manager->post(request, container);

    QObject::connect(reply, &QNetworkReply::finished, this, &HttpSender::finished);
    QObject::connect(reply, &QNetworkReply::uploadProgress, this, &HttpSender::uploadProgress);
    QObject::connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(error(QNetworkReply::NetworkError)));

    return HttpSender::NO_ERROR;
}
