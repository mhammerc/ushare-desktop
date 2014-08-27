#include "httppostupload.h"
#include "screenmanager.h"
#include <iostream>

HTTPPostUpload::HTTPPostUpload(FileManager *parent) : contentType("undefined"), parent(parent)
{
    reply = nullptr;
}

HTTPPostUpload::~HTTPPostUpload()
{
    container->deleteLater();
    file->deleteLater();
}

void HTTPPostUpload::setHost(QString const &host, int port)
{
    url.setUrl(host);
    url.setPort(port);
}

void HTTPPostUpload::setFile(QString const &pathToFile)
{
    this->pathToFile = pathToFile;
}

void HTTPPostUpload::setContentType(QString const &contentType)
{
    this->contentType = contentType;
}

void HTTPPostUpload::setUsername(const QString &username)
{
    this->username = username;
}

void HTTPPostUpload::setPassword(const QString &password)
{
    this->password = password;
}

void HTTPPostUpload::setPrivateKey(const QString &privateKey)
{
    this->privateKey = privateKey;
}

void HTTPPostUpload::sendFile()
{
    /* We include all the file in part */
    file = new QFile(pathToFile);

    if(!file->open(QIODevice::ReadOnly))
        QMessageBox::critical(0,"Uplimg","Can't open file");

    QHttpPart filePart;
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgFile\"; filename=\"" + file->fileName() + "\""));
    //filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(contentType));
    filePart.setBodyDevice(file);

    /* We include informations about file in other parts */
    QHttpPart fileTypePart;
    fileTypePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgFileType\""));
    fileTypePart.setBody(contentType.toStdString().c_str());

    /* Now we include user informations */
    QHttpPart usernamePart;
    usernamePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgUsername\""));
    usernamePart.setBody(username.toStdString().c_str());

    QHttpPart privateKeyPart;
    privateKeyPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgKey\""));
    privateKeyPart.setBody(privateKey.toStdString().c_str());

    QHttpPart passwordPart;
    passwordPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgPassword\""));
    passwordPart.setBody(QCryptographicHash::hash(password.toStdString().c_str(), QCryptographicHash::Sha1).toHex());

    QHttpPart uplimgVersionPart;
    uplimgVersionPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgVersion\""));
    uplimgVersionPart.setBody(Uplimg::version.toStdString().c_str());

    container = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    container->append(filePart);
    container->append(fileTypePart);
    container->append(usernamePart);
    container->append(privateKeyPart);
    container->append(passwordPart);
    container->append(uplimgVersionPart);

    QNetworkRequest request;
    request.setUrl(url);

    manager = new QNetworkAccessManager;
    reply = manager->post(request, container);

    reply->setParent(container);
    file->setParent(container);
    manager->setParent(reply);

    QObject::connect(reply, SIGNAL(finished()), parent, SLOT(fileSendedTroughHTTP()));
}
