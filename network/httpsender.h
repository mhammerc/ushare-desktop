#ifndef HTTPSENDER_H
#define HTTPSENDER_H


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

class HttpSender : public QThread
{
    Q_OBJECT
public:
    enum Status
    {
        FILE_ERROR,
        NO_ERROR
    };

    HttpSender();

    void run() Q_DECL_OVERRIDE
    {
        Status status = this->sendFile();
        if(status == Status::NO_ERROR)
            this->exec();

        emit statusChanged(status);
    }

public slots:
    /** Upload settings setters **/
    void setHost(QString const &host, int port)
    {
        url.setUrl(host);
        url.setPort(port);
    }

    void setFile(QString const &pathToFile)
    {
        this->pathToFile = pathToFile;
    }

    void setPasteSettings(QByteArray const &lang, QString const &langHR)
    {
        this->lang = lang;
        this->langHR = langHR;
    }

    void setUsername(QString const &username)
    {
        this->username = username;
    }

    void setPrivateKey(QString const &privateKey)
    {
        this->privateKey = privateKey;
    }

    void setUplimgVersion(QString const &uplimgVersion)
    {
        this->uplimgVersion = uplimgVersion;
    }

    QString getResponse()
    {
        return QString(reply->readAll());
    }

signals:
    void finished();
    void uploadProgress(qint64 bytesSent, qint64 bytesTotal);
    void error(QNetworkReply::NetworkError);
    void statusChanged(Status);


protected:
    Status sendFile();

    QUrl url;
    QString pathToFile;
    QString username;
    QString privateKey;
    QString uplimgVersion;
    QFile * file;
    /* Paste specific */
    QByteArray lang;
    QString langHR;
    /* internal network objects */
    QNetworkReply * reply;
    QNetworkAccessManager * manager;
    QHttpMultiPart * container;
};

#endif // HTTPSENDER_H
