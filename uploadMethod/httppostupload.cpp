#include "httppostupload.h"
#include "screenmanager.h"


HTTPPostUpload::HTTPPostUpload(FileManager *parent)
{
    contentType = "image";
    isFileSended = false;
    reply = 0;
    this->parent = parent;
}

HTTPPostUpload::~HTTPPostUpload()
{
    container->deleteLater();
    file->deleteLater();
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

    /* File Part */
    QHttpPart filePart;
    file = new QFile(pathToFile);

    if(!file->open(QIODevice::ReadOnly))
        QMessageBox::critical(0,"!!","");

    filePart.setBodyDevice(file);
    filePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"" + fileFieldName + "\"; filename=\"" + file->fileName() + "\""));
    filePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant(contentType));

    /* File type part */
    QHttpPart fileTypePart;
    fileTypePart.setHeader(QNetworkRequest::ContentTypeHeader, QVariant("text/plain"));
    fileTypePart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgFileType\""));
    fileTypePart.setBody(contentType.toLatin1());

    container->append(filePart);
    container->append(fileTypePart);

    QNetworkRequest request;
    request.setUrl(url);

    manager = new QNetworkAccessManager;
    reply = manager->post(request, container);

    reply->setParent(container);
    manager->setParent(reply);

    QObject::connect(reply, SIGNAL(finished()), parent, SLOT(fileSendedTroughHTTP()));
}
