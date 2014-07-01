#include "httppostupload.h"
#include "screenmanager.h"



HTTPPostUpload::HTTPPostUpload()
{
    isFileSended = false;
    reply = 0;
}

HTTPPostUpload::~HTTPPostUpload() {}

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
    QHttpMultiPart * container = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    QHttpPart filePart;
    QFile * file = new QFile(pathToFile);

    if(!file->open(QIODevice::ReadOnly))
        QMessageBox::critical(0,"!!","");

    filePart.setBodyDevice(file);
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + fileFieldName + "\"; filename=\"" + file->fileName() + "\""));
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(contentType));

    container->append(filePart);

    QNetworkRequest request;
    request.setUrl(url);

    QNetworkAccessManager * manager = new QNetworkAccessManager;

    delete reply;
    reply = manager->post(request, container);
}
