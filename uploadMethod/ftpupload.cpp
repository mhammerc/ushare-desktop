#include "ftpupload.h"
#include "screenmanager.h"


FTPUpload::FTPUpload(const File &file, QString const &host, unsigned int const port, QString const &username, QString const &password, QString const &basePath, FileManager * parent)
    : ftpClient(new sf::Ftp()), status(Uplimg::FTP_WAITING)
{
    this->file = file;
    this->parent = parent;
    this->host = host;
    this->port = port;
    this->username = username;
    this->password = password;
    this->basePath = basePath;
}

void FTPUpload::autoSendFile()
{
    if(openConnexion())
        {
            sendFile();
            closeConnexion();
        }
    emit operationFinished();
}

bool FTPUpload::sendFile()
{
    if (isOpenedConnection)
        {
            status = Uplimg::FTP_SENDING;
            sf::Ftp::Response response = ftpClient->upload(file.path.toStdString(), basePath.toStdString());
            if(response.isOk())
                {
                    status = Uplimg::FTP_SUCCESS;
                    return true;
                }
            else if (!response.isOk())
                {
                    status = Uplimg::FTP_UNKNOWN_ERROR;
                    std::cerr << response.getMessage();
                    return false;
                }
        }
    return false;
}

bool FTPUpload::openConnexion()
{
    status = Uplimg::FTP_CONNECTING;
    if (ftpClient->connect(sf::IpAddress(host.toStdString()), port).isOk())
        {
            if (ftpClient->login(username.toStdString(), password.toStdString()).isOk())
                {
                    isOpenedConnection = true;
                    status = Uplimg::FTP_CONNECTED;
                    return true;
                }
            else
                {
                    status = Uplimg::FTP_CANT_CONNECT;
                    return false;
                }
        }
    else
        {
            status = Uplimg::FTP_CANT_CONNECT;
            return false;
        }

    return false;
}

bool FTPUpload::closeConnexion()
{
    if (isOpenedConnection)
        {
            if (ftpClient->disconnect().isOk())
                {
                    isOpenedConnection = false;
                    return true;
                }
        }

    return false;
}

FTPUpload::~FTPUpload()
{
    this->closeConnexion();
}
