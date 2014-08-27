#pragma once
#include <QObject>
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QNetworkRequest>
#include <QUrl>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QThread>
#include <QMessageBox>
#include <QCryptographicHash>

#include <fstream>


class FileManager;

class HTTPPostUpload : public QThread
{
    Q_OBJECT
public:
    HTTPPostUpload(FileManager * parent);
    ~HTTPPostUpload();

    void setHost(QString const &host, int port);
    void setFile(QString const &pathToFile);
    void setContentType(QString const &contentType = "image");

    void setUsername(QString const &username);
    void setPassword(QString const &password);
    void setPrivateKey(QString const &privateKey);

    void sendFile();

    void run() Q_DECL_OVERRIDE
    {
        this->sendFile();
        this->exec();
    }

    QNetworkReply * reply;
    QNetworkAccessManager * manager;
    QHttpMultiPart * container;
    QFile * file;

protected:
    QUrl url;

    QString pathToFile;
    QString contentType;
    QString username;
    QString password;
    QString privateKey;

    FileManager * parent;
};

