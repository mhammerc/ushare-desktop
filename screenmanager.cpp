/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#include "screenmanager.h"
#include "systemtrayicon.h"


FileManager::FileManager(SystemTrayIcon *parent) :
    parent(parent),
    darkenFactor(10)
{
    QObject::connect(this, SIGNAL(canSend()), parent, SLOT(sendSelectedArea()));
}

void FileManager::autoSendFile(File const &file)
{
    lastFile = file;
    Uplimg::UploadMethod method = Uplimg::Utils::getUploadMethod();

    if (file.hasError)
        parent->throwErrorAlert(Uplimg::ErrorList::CANT_SAVE_IMAGE_TEMP);

    else if (method == Uplimg::UploadMethod::U_ERROR)
        parent->throwErrorAlert(Uplimg::ErrorList::UPLOAD_METHOD_NOT_CHOOSED);

    else if (method == Uplimg::UploadMethod::FTP)
        return sendFileTroughFTP(file);

    else if (method == Uplimg::UploadMethod::HTTP)
        return sendFileTroughHTTP(file);

    else if (method == Uplimg::UploadMethod::UPLIMG_WEB)
        return sendFileTroughUplimgWeb(file);

    else if (method == Uplimg::UploadMethod::LOCAL)
        parent->fileSended(lastFile);

    return;
}

void FileManager::sendFileTroughFTP(File const &file)
{
    ftp = new FTPUpload(this);

    ftp->setHost(settings.value(Reg::FTPHost).toString());
    ftp->setPort(settings.value(Reg::FTPPort).toInt());
    ftp->setUsername(settings.value(Reg::FTPUsername).toString());
    ftp->setPassword(settings.value(Reg::FTPPassword).toString());
    ftp->setBasepath(settings.value(Reg::FTPBasePath).toString());
    ftp->insertFile(file);

    QObject::connect(ftp, SIGNAL(operationFinished()), this, SLOT(fileSendedTroughFTP()));

    ftp->run();
}

void FileManager::fileSendedTroughFTP()
{
    Uplimg::FTPStatus status = ftp->status;

    ftp->terminate();
    ftp->deleteLater();
    ftp = nullptr;

    if(status == Uplimg::FTP_SUCCESS)
        parent->fileSended(lastFile);
    else if(status == Uplimg::FTP_UNKNOWN_ERROR)
        parent->throwErrorAlert(Uplimg::UPLOAD_FAIL);
    else if(status == Uplimg::FTP_CANT_CONNECT)
        parent->throwErrorAlert(Uplimg::FTP_CANT_CONNECT);
    else if(status == Uplimg::FTP_CANT_LOGIN)
        parent->throwErrorAlert(Uplimg::FTP_CANT_LOGIN);
    else if(status == Uplimg::FTP_CANT_PUT_FILE)
        parent->throwErrorAlert(Uplimg::FTP_CANT_PUT_FILE);
}

void FileManager::sendFileTroughUplimgWeb(File const &file)
{
    http = new HTTPPostUpload(this);
    http->setHost(UplimgWeb::host, UplimgWeb::port);
    http->setFile(file.path);
    http->setContentType(file.type);
    http->setLanguage(file.language, file.languageHR);
    http->setUsername(settings.value(Reg::UplimgWebUsername).toString());
    http->setPassword(settings.value(Reg::UplimgWebPassword).toString());
    http->start();
}

void FileManager::sendFileTroughHTTP(File const &file)
{
    http = new HTTPPostUpload(this);
    http->setHost(settings.value(Reg::HTTPHost).toString(), settings.value(Reg::HTTPPort).toInt());
    http->setFile(file.path);
    http->setContentType(file.type);
    http->setLanguage(file.language, file.languageHR);
    http->setUsername(settings.value(Reg::HTTPUsername).toString());
    http->setPassword(settings.value(Reg::HTTPPassword).toString());
    http->setPrivateKey(settings.value(Reg::HTTPPrivateKey).toString());
    http->start();
}


/** Windows and linux not work same for capturing area */

#ifdef _WIN32
File FileManager::captureSelectedZone(File const &file)
{
    this->lastFile = file;

    screen = QGuiApplication::screens()[0];
    screenNumber = 0;
    if (screen)
        {
            originalScreenshot = screen->grabWindow(0, screen->virtualGeometry().x(), screen->virtualGeometry().y(), screen->virtualGeometry().width(), screen->virtualGeometry().height());

            if (!originalScreenshot.isNull())
                {
                    fullScreenPicture = new SelectAreaBand(this);
                    fullScreenPicture->setPixmap(originalScreenshot);
                    fullScreenPicture->selectArea();
                    fullScreenPicture->setGeometry(screen->virtualGeometry().x(),screen->virtualGeometry().y(),screen->virtualSize().width(), screen->virtualSize().height());
                }
        }

    return file;
}
#endif

#ifdef __linux__
File FileManager::captureSelectedZone(File const &file)
{
    this->lastFile = file;

    screen = QGuiApplication::primaryScreen();

    if (screen)
        {
            originalScreenshot = screen->grabWindow(0, screen->geometry().x(), screen->geometry().y(), screen->geometry().width(), screen->geometry().height());

            if (!originalScreenshot.isNull())
                {
                    fullScreenPicture = new SelectAreaBand(this);
                    fullScreenPicture->setPixmap(originalScreenshot);
                    fullScreenPicture->selectArea();
                }
        }

    return file;
}
#endif

void FileManager::areaPictureTaken(QRect area)
{
    originalScreenshot = originalScreenshot.copy(area);

    if(Uplimg::Utils::getImageFormat() == Uplimg::ImageFormat::JPEG)
        originalScreenshot.save(lastFile.path, 0, Uplimg::Utils::getImageQuality());
    else if(Uplimg::Utils::getImageFormat() == Uplimg::ImageFormat::PNG)
        originalScreenshot.save(lastFile.path, 0, 0);

    emit canSend();
    fullScreenPicture->deleteLater();
}

void FileManager::areaPictureCanceled()
{
    parent->lastActionFinished();
    parent->setIcon(QIcon(":/icon/waiting.png"));
    fullScreenPicture->deleteLater();
}

QPixmap FileManager::darkenPicture(const QPixmap &picture)
{
    QImage image = picture.toImage();
    const int width = image.width();
    const int height = image.height();

    for (int i = 0; i < width; ++i)
        {
            for (int j = 0; j < height; ++j)
                {
                    QColor color = QColor::fromRgb(image.pixel(i, j));

                    if(color.value() - darkenFactor > 0)
                        color.setHsv(color.hue(), color.saturation(), color.value() - darkenFactor);
                    else
                        color.setHsv(color.hue(), color.saturation(), 0);
                    image.setPixel(i, j, color.rgb());
                }
        }

    return QPixmap::fromImage(image);
}

File FileManager::captureFullScreen(File &file)
{
    QScreen * screen = QGuiApplication::primaryScreen();
    QPixmap screenshot;

    if (screen)
        {
            screenshot = screen->grabWindow(0);

            if(Uplimg::Utils::getImageFormat() == Uplimg::ImageFormat::JPEG)
                {
                    if (!screenshot.save(file.path, 0, Uplimg::Utils::getImageQuality()))
                        {
                            file.error();
                            return file;
                        }
                }
            else if(Uplimg::Utils::getImageFormat() == Uplimg::ImageFormat::PNG)
                {
                    if (!screenshot.save(file.path, 0, 0))
                        {
                            file.error();
                            return file;
                        }
                }
        }
    else
        file.error();

    return file;

}

void FileManager::startPastMode()
{
    paste = new PasteWindow(this);
    paste->show();
}

FileManager::~FileManager() {}

void FileManager::fileSendedTroughHTTP()
{
    if(http->reply->error() == QNetworkReply::NetworkError::NoError)
        {
            http->terminate();
            http->wait();
            var::lastUrl = QString(http->reply->readAll());
            http->deleteLater();
            http = nullptr;
            parent->fileSended(lastFile);

        }
    else if(http->reply->error() != QNetworkReply::NetworkError::NoError)
        {
            http->terminate();
            http->wait();
            http->deleteLater();
            http = nullptr;
            parent->throwErrorAlert(Uplimg::UPLOAD_FAIL);
        }

}

void FileManager::pasteReady(const PasteContent &pasteContent)
{
    paste->close();
    paste->deleteLater();
    paste = nullptr;

    File file;
    if(pasteContent.fileTitle == "undefined")
        {
            file.realName = Uplimg::Utils::getNewFileName(".txt");
            file.path = Uplimg::Utils::getFileTempPath(file.realName);
        }
    else
        {
            file.wantedName = pasteContent.fileTitle;
            file.path = Uplimg::Utils::getFileTempPath(file.wantedName);
        }

    file.type = "paste";
    file.language = pasteContent.fileContentLanguage;
    file.languageHR = pasteContent.fileContentLanguageHR;
    QFile physicFile(file.path);
    physicFile.open(QIODevice::WriteOnly);
    physicFile.write(pasteContent.fileContent.toUtf8());
    physicFile.close();
    parent->newActionStarted();
    autoSendFile(file);
}
