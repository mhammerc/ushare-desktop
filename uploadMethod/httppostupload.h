/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

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
    void setLanguage(QByteArray const &lang, QString const &langHR) { this->lang = lang; this->langHR = langHR; }

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

    /** Paste specific */
    QByteArray lang;
    QString langHR;

    FileManager * parent;
};

