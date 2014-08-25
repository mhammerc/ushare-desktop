#include "httppostupload.h"
#include "screenmanager.h"
#include <iostream>

HTTPPostUpload::HTTPPostUpload(FileManager *parent) : contentType("undefined"), destinationFilename("undefined"), parent(parent)
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

void HTTPPostUpload::setFile(QString const &pathToFile, const QString &fileFieldName)
{
    this->pathToFile = pathToFile;
    this->fileFieldName = fileFieldName;
}

void HTTPPostUpload::setContentType(QString const &contentType)
{
    this->contentType = contentType;
}

void HTTPPostUpload::setDestinationFileName(QString const &destinationFilename)
{
    this->destinationFilename = destinationFilename;
}

void HTTPPostUpload::sendFile()
{
    container = new QHttpMultiPart(QHttpMultiPart::FormDataType);

    /* We include all the file in part */
    QHttpPart filePart;
    file = new QFile(pathToFile);

    if(!file->open(QIODevice::ReadOnly))
        QMessageBox::critical(0,"!!","");

    filePart.setBodyDevice(file);
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + fileFieldName + "\"; filename=\"" + file->fileName() + "\""));
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(contentType));

    /* We include informations about file in other parts */
    QHttpPart fileTypePart;
    fileTypePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    fileTypePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgFileType\""));
    fileTypePart.setBody(contentType.toUtf8());

    QHttpPart destinationFilenamePart;
    destinationFilenamePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    destinationFilenamePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgFilename\""));
    destinationFilenamePart.setBody(destinationFilename.toUtf8());

    container->append(filePart);
    container->append(fileTypePart);
    container->append(destinationFilenamePart);

    QNetworkRequest request;
    request.setUrl(url);

    manager = new QNetworkAccessManager;
    reply = manager->post(request, container);

    reply->setParent(container);
    manager->setParent(reply);

    QObject::connect(reply, SIGNAL(finished()), parent, SLOT(fileSendedTroughHTTP()));
}
