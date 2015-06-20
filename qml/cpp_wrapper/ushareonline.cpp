/**
 * This file (c) by : - Martin Hammerchmidt alias Imote
 *
 * This file is licensed under a
 * GNU GENERAL PUBLIC LICENSE V3.0
 *
 * See the LICENSE file to learn more.
 *
 * If you have contributed to this file, add your name to authors list.
*/

#include "ushareonline.h"

std::map<QByteArray, QByteArray> UShareOnline::emptyMap = std::map<QByteArray, QByteArray>();

UShareOnline::UShareOnline(QObject *parent) : QObject(parent), isConnected(false), requestInProgress(false), manager(nullptr), httpMultiPart(nullptr), reply(nullptr)
{}

void UShareOnline::setAccountKey(QString accountKey)
{
    if(this->accountKey == accountKey) return;

    this->accountKey = accountKey;
    emit accountKeyChanged(accountKey);
}

void UShareOnline::setPrivateKey(QString privateKey)
{
    if(this->privateKey == privateKey) return;

    this->privateKey = privateKey;
    emit privateKeyChanged(privateKey);
}

void UShareOnline::setConnected(bool isConnected)
{
    if(this->isConnected == isConnected) return;

    this->isConnected = isConnected;
    emit isConnectedChanged(isConnected);
}

void UShareOnline::setRequestInProgress(bool requestInProgress)
{
    if(this->requestInProgress == requestInProgress) return;

    this->requestInProgress = requestInProgress;
    emit requestInProgressChanged(requestInProgress);
}

void UShareOnline::connect(QString username, QString password)
{
    callback = std::bind(&UShareOnline::_connected, this, std::placeholders::_1);

    std::map<QByteArray, QByteArray> headers;
    std::map<QByteArray, QByteArray> body;

    body.insert(std::make_pair(QByteArray("username"), username.toLocal8Bit()));
    body.insert(std::make_pair(QByteArray("password"), QmlDesktop::encryptAsSha256(password).toLocal8Bit()));
    body.insert(std::make_pair(QByteArray("source"), Shared::appVersion.toLocal8Bit()));

    post(Shared::authUrl, headers, body);
}

void UShareOnline::register_(QString username, QString password, QString email)
{
    callback = std::bind(&UShareOnline::_registered, this, std::placeholders::_1);

    std::map<QByteArray, QByteArray> headers;
    std::map<QByteArray, QByteArray> body;

    body.insert(std::make_pair(QByteArray("username"), username.toLocal8Bit()));
    body.insert(std::make_pair(QByteArray("password"), QmlDesktop::encryptAsSha256(password).toLocal8Bit()));
    body.insert(std::make_pair(QByteArray("email"), email.toLocal8Bit()));
    body.insert(std::make_pair(QByteArray("source"), Shared::appVersion.toLocal8Bit()));

    post(Shared::registerUrl, headers, body);
}

void UShareOnline::getUploadList(int limit)
{
    callback = std::bind(&UShareOnline::_gotUploadList, this, std::placeholders::_1);

    std::map<QByteArray, QByteArray> headers;
    headers.insert(std::make_pair(QByteArray("accountkey"), accountKey.toLocal8Bit()));
    headers.insert(std::make_pair(QByteArray("privatekey"), privateKey.toLocal8Bit()));
    headers.insert(std::make_pair(QByteArray("limit"), QVariant(limit).toByteArray()));
    headers.insert(std::make_pair(QByteArray("source"), Shared::appVersion.toLocal8Bit()));

    get(Shared::getUploadList, headers);
}

void UShareOnline::getUserInfos()
{
    callback = std::bind(&UShareOnline::_gotUserInfos, this, std::placeholders::_1);

    std::map<QByteArray, QByteArray> headers;
    headers.insert(std::make_pair(QByteArray("accountkey"), accountKey.toLocal8Bit()));
    headers.insert(std::make_pair(QByteArray("privatekey"), privateKey.toLocal8Bit()));
    headers.insert(std::make_pair(QByteArray("source"), Shared::appVersion.toLocal8Bit()));

    get(Shared::getUserInfo, headers);
}

void UShareOnline::editFilePassword(QString newPassword, QString shortName)
{
    callback = std::bind(&UShareOnline::_filePasswordEdited, this, std::placeholders::_1);

    std::map<QByteArray, QByteArray> headers;

    std::map<QByteArray, QByteArray> body;
    body.insert(std::make_pair(QByteArray("accountkey"), accountKey.toLocal8Bit()));
    body.insert(std::make_pair(QByteArray("privatekey"), privateKey.toLocal8Bit()));
    body.insert(std::make_pair(QByteArray("shortname"), shortName.toLocal8Bit()));
    body.insert(std::make_pair(QByteArray("password"), newPassword.toLocal8Bit()));
    body.insert(std::make_pair(QByteArray("source"), Shared::appVersion.toLocal8Bit()));

    post(Shared::editPasswordUrl, headers, body);
}

void UShareOnline::deleteFile(QString shortName)
{
    callback = std::bind(&UShareOnline::_fileDeleted, this, std::placeholders::_1);

    std::map<QByteArray, QByteArray> headers;

    std::map<QByteArray, QByteArray> body;
    body.insert(std::make_pair(QByteArray("accountkey"), accountKey.toLocal8Bit()));
    body.insert(std::make_pair(QByteArray("privatekey"), privateKey.toLocal8Bit()));
    body.insert(std::make_pair(QByteArray("shortname"), shortName.toLocal8Bit()));
    body.insert(std::make_pair(QByteArray("source"), Shared::appVersion.toLocal8Bit()));

    post(Shared::deleteUrl, headers, body);
}

void UShareOnline::disconnect()
{
    setConnected(false);

    setAccountKey("");
    setPrivateKey("");
    Settings::setEntry(SettingsKeys::ACCOUNT_KEY, "");
    Settings::setEntry(SettingsKeys::PRIVATE_KEY, "");
}

void UShareOnline::getGravatarUrl(QString email)
{
    callback = std::bind(&UShareOnline::_gotGravatarUrl, this, std::placeholders::_1);

    email = email.toLower();
    email = QmlDesktop::encryptAsMD5(email);

    QString gravatarUrl = "http://www.gravatar.com/" + email + ".json";

    get(gravatarUrl);
}

void UShareOnline::getUpdates()
{
    callback = std::bind(&UShareOnline::_gotUpdates, this, std::placeholders::_1);

    get(Shared::updateInfoUrl);
}

void UShareOnline::get(const QUrl &url, std::map<QByteArray, QByteArray> &headers)
{
    sendHttpRequest(RequestType::Get, url, headers);
}

void UShareOnline::post(const QUrl &url, std::map<QByteArray, QByteArray> &headers, std::map<QByteArray, QByteArray> &body)
{
    sendHttpRequest(RequestType::Post, url, headers, body);
}

void UShareOnline::sendHttpRequest(const UShareOnline::RequestType type, const QUrl &url, std::map<QByteArray, QByteArray> &headers, std::map<QByteArray, QByteArray> &body)
{
    if(requestInProgress)
        return;

    setRequestInProgress(true);

    QNetworkRequest request;
    request.setUrl(url);

    /* Inserting every headers into the request */
    for(auto& header : headers)
    {
        request.setRawHeader(header.first, header.second);
    }

    if(!body.empty())
    {
        httpMultiPart = new QHttpMultiPart(QHttpMultiPart::FormDataType);

        for(auto& bodyPart : body)
        {
            QHttpPart httpPart;

            QVariant header = QVariant(QString(("form-data; name=\"" + bodyPart.first.toStdString() + "\"").c_str()).toLocal8Bit());
            httpPart.setHeader(QNetworkRequest::ContentDispositionHeader, header);

            httpPart.setBody(bodyPart.second);

            httpMultiPart->append(httpPart);
        }
    }

    manager = new QNetworkAccessManager(this);

    if(httpMultiPart)
    {
        httpMultiPart->setParent(manager);
        reply = manager->post(request, httpMultiPart);
        reply->setParent(manager);
    }
    else
    {
        switch(type)
        {
        case RequestType::Get:
            reply = manager->get(request);
            break;
        case RequestType::Post:
            reply = manager->post(request, QByteArray());
            break;
        }
    }

    QObject::connect(reply, &QNetworkReply::finished, this, &UShareOnline::requestFinished);
    QObject::connect(reply, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(networkError(QNetworkReply::NetworkError)));
}

void UShareOnline::_connected(QByteArray response)
{
    QJsonDocument document = QJsonDocument::fromJson(response);
    QVariantMap result = document.object().toVariantMap();

    if(result["success"].toBool())
    {
        setAccountKey(result["accountkey"].toString());
        setPrivateKey(result["privatekey"].toString());
        Settings::setEntry(SettingsKeys::ACCOUNT_KEY, result["accountkey"]);
        Settings::setEntry(SettingsKeys::PRIVATE_KEY, result["privatekey"]);
        setConnected(true);
    }
    else
    {
        setConnected(false);
    }

    emit connected(result);
}

void UShareOnline::_registered(QByteArray response)
{
    QJsonDocument document = QJsonDocument::fromJson(response);
    QVariantMap result = document.object().toVariantMap();

    emit registered(result);
}

void UShareOnline::_gotUploadList(QByteArray response)
{
    QJsonDocument document = QJsonDocument::fromJson(response);
    QVariantMap result = document.object().toVariantMap();

    emit gotUploadList(result);
}

void UShareOnline::_gotUserInfos(QByteArray response)
{
    QJsonDocument document = QJsonDocument::fromJson(response);
    QVariantMap result = document.object().toVariantMap();

    emit gotUserInfos(result);
}

void UShareOnline::_filePasswordEdited(QByteArray response)
{
    QJsonDocument document = QJsonDocument::fromJson(response);
    QVariantMap result = document.object().toVariantMap();

    emit filePasswordEdited(result);
}

void UShareOnline::_fileDeleted(QByteArray response)
{
    QJsonDocument document = QJsonDocument::fromJson(response);
    QVariantMap result = document.object().toVariantMap();

    emit fileDeleted(result);
}

void UShareOnline::_gotGravatarUrl(QByteArray response)
{
    QJsonDocument document = QJsonDocument::fromJson(response);
    QVariantMap result = document.object().toVariantMap();

    emit gotGravatarUrl(result);
}

void UShareOnline::_gotUpdates(QByteArray response)
{
    QJsonDocument document = QJsonDocument::fromJson(response);
    QVariantList result = document.array().toVariantList();

    emit gotUpdates(result);
}

void UShareOnline::requestFinished()
{
    setRequestInProgress(false);
    callback(reply->readAll());
    manager->deleteLater();

    manager = nullptr;
    httpMultiPart = nullptr;
    reply = nullptr;
}

void UShareOnline::networkError(QNetworkReply::NetworkError)
{
    /*manager->deleteLater();

    manager = nullptr;
    httpMultiPart = nullptr;
    reply = nullptr;*/
}
