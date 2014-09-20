/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#include "httppostupload.h"
#include "screenmanager.h"
#include <iostream>

HTTPPostUpload::HTTPPostUpload(FileManager *parent) : contentType("undefined"), parent(parent), lang("undefined")
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

    QHttpPart passwordPart;
    passwordPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgPassword\""));
    if(password != "") passwordPart.setBody(QCryptographicHash::hash(password.toStdString().c_str(), QCryptographicHash::Sha1).toHex());
    else passwordPart.setBody("");

    QHttpPart uplimgVersionPart;
    uplimgVersionPart.setHeader(QNetworkRequest::ContentDispositionHeader, QVariant("form-data; name=\"uplimgVersion\""));
    uplimgVersionPart.setBody(Uplimg::version.toStdString().c_str());

    container = new QHttpMultiPart(QHttpMultiPart::FormDataType);
    container->append(filePart);
    container->append(fileTypePart);
    container->append(fileLanguagePart);
    container->append(fileLanguageHRPart);
    container->append(usernamePart);
    container->append(privateKeyPart);
    container->append(passwordPart);
    container->append(uplimgVersionPart);

    QNetworkRequest request;
    request.setUrl(url);

    manager = new QNetworkAccessManager;

    reply = manager->post(request, container);

    QObject::connect(reply, SIGNAL(finished()), parent, SLOT(fileSendedTroughHTTP()));

    reply->setParent(container);
    file->setParent(container);
    manager->setParent(reply);
}
