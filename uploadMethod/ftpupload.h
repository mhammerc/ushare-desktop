#ifndef FTPUPLOAD_H
#define FTPUPLOAD_H

#include <SFML/Network.hpp>


#include <memory>
#include <string>
#include <iostream>

class FTPUpload
{
public:
    ~FTPUpload();
    FTPUpload(const std::string &host, unsigned short port, const std::string &username, const std::string &password, const std::string &basePath);

    bool openConnexion();
    bool closeConnexion();

    bool sendFile(std::string pathToLocalFile);

protected:
    std::unique_ptr<sf::Ftp> ftpClient;

    std::string host;
    unsigned short port;
    std::string username;
    std::string password;
    std::string basePath;

    bool isOpenedConnection;

};

#endif // FTPUPLOAD_H
