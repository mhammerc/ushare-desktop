#include "httppostupload.h"
#include "screenmanager.h"


HTTPPostUpload::HTTPPostUpload()
{
    isFileSended = false;
    reply = 0;
}

HTTPPostUpload::~HTTPPostUpload()
{
    delete container;
    delete file;
}

void HTTPPostUpload::setHost(const QString &host, int port)
{
    url.setUrl(host);
    url.setPort(port);
}

void HTTPPostUpload::setFile(const QString &pathToFile, const QString &fileFieldName)
{
    this->pathToFile = pathToFile;
    this->fileFieldName = fileFieldName;
}

void HTTPPostUpload::setContentType(const QString &contentType)
{
    this->contentType = contentType;
}

void HTTPPostUpload::sendFile()
{
    container = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart filePart;
    file = new QFile(pathToFile);

    if(!file->open(QIODevice::ReadOnly))
        QMessageBox::critical(0,"!!","");

    filePart.setBodyDevice(file);
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + fileFieldName + "\"; filename=\"" + file->fileName() + "\""));
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(contentType));

    container->append(filePart);

    QNetworkRequest request;
    request.setUrl(url);

    manager = new QNetworkAccessManager;
    reply = manager->post(request, container);

    reply->setParent(container);
    manager->setParent(reply);
}
