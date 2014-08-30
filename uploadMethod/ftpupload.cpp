/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#include "ftpupload.h"
#include "screenmanager.h"


FTPUpload::FTPUpload(FileManager * parent)
    : status(Uplimg::FTP_WAITING), ftpClient(new sf::Ftp())
{
    this->parent = parent;
}

void FTPUpload::setHost(const QString &host)
{
    this->host = host;
}

void FTPUpload::setPort(const unsigned int port)
{
    this->port = port;
}

void FTPUpload::setUsername(const QString &username)
{
    this->username = username;
}

void FTPUpload::setPassword(const QString &password)
{
    this->password = password;
}

void FTPUpload::setBasepath(const QString &basePath)
{
    this->basePath = basePath;
}

void FTPUpload::insertFile(const File &file)
{
    this->file = file;
}

void FTPUpload::autoSendFile()
{
    if(!openConnexion())
        {
            emit operationFinished();
            return;
        }

    sendFile();
    closeConnexion();

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
                    status = Uplimg::FTP_CANT_PUT_FILE;
                    std::cerr << response.getMessage();
                    return false;
                }
        }
    return false;
}

bool FTPUpload::openConnexion()
{
    status = Uplimg::FTP_CONNECTING;

    if (ftpClient->connect(sf::IpAddress(host.toStdString()), port, sf::seconds(3)).isOk())
        {
            if (ftpClient->login(username.toStdString(), password.toStdString()).isOk())
                {
                    isOpenedConnection = true;
                    status = Uplimg::FTP_CONNECTED;
                    return true;
                }
            else
                {
                    status = Uplimg::FTP_CANT_LOGIN;
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
