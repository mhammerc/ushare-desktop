#include "httpsender.h"

HttpSender::HttpSender(){}

HttpSender::Status HttpSender::sendFile()
{

    /* We include all the file in part of the request */
    file = new QFile(pathToFile, this);

    if(!file->open(QIODevice::ReadOnly)) return HttpSender::FILE_ERROR;

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgFile\"; filename=\"" + file->fileName() + "\""));
    filePart.setBodyDevice(file);

    /* We include informations about file in other parts */
    QHttpPart fileLanguagePart;
    fileLanguagePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgFileLanguage\""));
    fileLanguagePart.setBody(lang);

    QHttpPart fileLanguageHRPart;
    fileLanguageHRPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgFileLanguageHR\""));
    fileLanguageHRPart.setBody(langHR.toStdString().c_str());

    /* Now we include user informations */
    QHttpPart usernamePart;
    usernamePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgUsername\""));
    usernamePart.setBody(username.toStdString().c_str());

    QHttpPart privateKeyPart;
    privateKeyPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgKey\""));
    privateKeyPart.setBody(privateKey.toStdString().c_str());

    QHttpPart uplimgVersionPart;
    uplimgVersionPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgVersion\""));
    uplimgVersionPart.setBody(uplimgVersion.toStdString().c_str());

    container = new QHttpMultiPart(QHttpMultiPart::FormDataType, this);
    container->append(filePart);
    container->append(privateKeyPart);
    container->append(usernamePart);
    container->append(fileLanguagePart);
    container->append(fileLanguageHRPart);
    container->append(uplimgVersionPart);

    QNetworkRequest request;
    request.setUrl(url);

    manager = new QNetworkAccessManager(this);
    reply = manager->post(request, container);

    QObject::connect(reply, &QNetworkReply::finished, this, &HttpSender::finished);
    QObject::connect(reply, &QNetworkReply::uploadProgress, this, &HttpSender::uploadProgress);
    QObject::connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(error(QNetworkReply::NetworkError)));

    return HttpSender::NO_ERROR;
}
