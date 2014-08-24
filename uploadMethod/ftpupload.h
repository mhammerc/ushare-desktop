#ifndef FTPUPLOAD_H
#define FTPUPLOAD_H

#include <SFML/Network.hpp>

#include <string>
#include <memory>
#include <iostream>
#include <QThread>
#include <QString>
#include "shared.h"

class FileManager;

class FTPUpload : public QThread
{
    Q_OBJECT
public:
    ~FTPUpload();
    FTPUpload(File const& file, QString const &host, unsigned int const port, QString const &username, QString const &password, QString const &basePath, FileManager * parent);

    void autoSendFile();
    Uplimg::FTPStatus status;

    void run() Q_DECL_OVERRIDE
    {
        this->autoSendFile();
        this->exec();
    }

protected:
    bool openConnexion();
    bool closeConnexion();
    bool sendFile();

    std::unique_ptr<sf::Ftp> ftpClient;

    File file;
    QString host;
    unsigned int port;
    QString username;
    QString password;
    QString basePath;

    FileManager * parent;
    bool isOpenedConnection;

signals:
    void operationFinished();

};

#endif // FTPUPLOAD_H
