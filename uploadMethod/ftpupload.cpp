#include "ftpupload.h"


FTPUpload::FTPUpload(const std::string &host, unsigned short port, const std::string &username, const std::string &password, const std::string &basePath)
    : ftpClient(new sf::Ftp())
{
    this->host = host;
    this->port = port;
    this->username = username;
    this->password = password;
    this->basePath = basePath;
}

bool FTPUpload::sendFile(std::string pathToLocalFile)
{

    if (isOpenedConnection)
        {
            sf::Ftp::Response response = ftpClient->upload(pathToLocalFile, basePath);
            if (!response.isOk())
                {
                    std::cerr << response.getMessage();
                    return false;
                }
            return true;
        }

    return false;
}

bool FTPUpload::openConnexion()
{


    if (ftpClient->connect(sf::IpAddress(host), port).isOk())
        {
            if (ftpClient->login(username, password).isOk())
                {
                    isOpenedConnection = true;
                    return true;
                }
            else return false;
        }
    else return false;

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
