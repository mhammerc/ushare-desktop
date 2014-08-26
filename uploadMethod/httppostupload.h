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

#include <fstream>


class FileManager;

class HTTPPostUpload : public QThread
{
    Q_OBJECT
public:
    HTTPPostUpload(FileManager * parent);
    ~HTTPPostUpload();

    void setHost(QString const &host, int port);
    void setFile(QString const &pathToFile, const QString &fileFieldName);
    void setContentType(QString const &contentType = "image");
    void setWantedFileName(QString const& destinationFilename);

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
    QString fileFieldName;
    QString contentType;
    QString destinationFilename; //Needed file name for downloading

    FileManager * parent;
};

