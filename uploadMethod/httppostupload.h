#pragma once
#include <QHttpMultiPart>
#include <QHttpPart>
#include <QNetworkRequest>
#include <QUrl>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QString>
#include <QObject>
#include <QThread>
#include <QMessageBox>

#include <fstream>

#include <SFML/System.hpp>

#include <iostream>

class HTTPPostUpload : public QThread
{
    Q_OBJECT
public:
    HTTPPostUpload();
    ~HTTPPostUpload();

    bool isFileSended;

    void setHost(const QString &host, int port);

    void setFile(const QString &pathToFile, const QString &fileFieldName);
    void setContentType(const QString &contentType = "image/png");

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

    bool canGetReply()
    {
        if(reply != 0) return true;
        else return false;
    }

protected:
    QUrl url;

    QString pathToFile;
    QString fileFieldName;
    QString contentType;
};

