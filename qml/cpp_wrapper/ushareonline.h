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

#ifndef USHAREONLINE_H
#define USHAREONLINE_H

#include <QObject>
#include <QString>
#include <QUrl>
#include <QByteArray>
#include <QNetworkRequest>
#include <QNetworkAccessManager>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QNetworkReply>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QVariantMap>
#include <QVariantList>

#include "core/shared.h"
#include "core/settings.h"
#include "desktop.h"

#include <functional>
#include <map>
#include <string>

class UShareOnline : public QObject
{
    Q_OBJECT

    Q_PROPERTY(bool connected MEMBER isConnected WRITE setConnected NOTIFY isConnectedChanged)
    Q_PROPERTY(bool loading MEMBER requestInProgress WRITE setRequestInProgress NOTIFY requestInProgressChanged)
    Q_PROPERTY(QString accountKey MEMBER accountKey WRITE setAccountKey NOTIFY accountKeyChanged)
    Q_PROPERTY(QString privateKey MEMBER privateKey WRITE setPrivateKey NOTIFY privateKeyChanged)

public:
    enum RequestType
    {
        Get,
        Post
    };

    explicit UShareOnline(QObject *parent = 0);

private:
    QString accountKey;
    QString privateKey;

    bool isConnected;
    bool requestInProgress;

    void setAccountKey(QString accountKey);
    void setPrivateKey(QString privateKey);
    void setConnected(bool isConnected);
    void setRequestInProgress(bool requestInProgress);

    QNetworkAccessManager * manager;
    QHttpMultiPart * httpMultiPart;
    QNetworkReply * reply;

    /* Callbacks */
    std::function<void(QByteArray)> callback;
    void _connected(QByteArray response);
    void _registered(QByteArray response);
    void _gotUploadList(QByteArray response);
    void _gotUserInfos(QByteArray response);
    void _filePasswordEdited(QByteArray response);
    void _fileDeleted(QByteArray response);

    void _gotGravatarUrl(QByteArray response);

    void _gotUpdates(QByteArray response);


    static std::map<QByteArray, QByteArray> emptyMap;
    void get(const QUrl &url, std::map<QByteArray, QByteArray> &headers = emptyMap);
    void post(const QUrl &url, std::map<QByteArray, QByteArray> &headers = emptyMap, std::map<QByteArray, QByteArray> &body = emptyMap);
    void sendHttpRequest(const RequestType type, const QUrl &url, std::map<QByteArray, QByteArray> &headers = emptyMap, std::map<QByteArray, QByteArray> &body = emptyMap);


signals:
    void connected(QVariantMap response);
    void registered(QVariantMap response);
    void gotUploadList(QVariantMap response);
    void gotUserInfos(QVariantMap response);
    void filePasswordEdited(QVariantMap response);
    void fileDeleted(QVariantMap response);

    void gotGravatarUrl(QVariantMap response);

    void gotUpdates(QVariantList response);

    void accountKeyChanged(QString);
    void privateKeyChanged(QString);
    void isConnectedChanged(bool);
    void requestInProgressChanged(bool);


public slots:
    void requestFinished();
    void networkError(QNetworkReply::NetworkError);

public:
    Q_INVOKABLE void connect(QString username, QString password);
    Q_INVOKABLE void register_(QString username, QString password, QString email);
    Q_INVOKABLE void getUploadList(int limit);
    Q_INVOKABLE void getUserInfos();
    Q_INVOKABLE void editFilePassword(QString newPassword, QString shortName);
    Q_INVOKABLE void deleteFile(QString shortName);
    Q_INVOKABLE void disconnect();

    Q_INVOKABLE void getGravatarUrl(QString email);

    Q_INVOKABLE void getUpdates();
};

#endif // USHAREONLINE_H
