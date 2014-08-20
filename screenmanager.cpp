#include "screenmanager.h"
#include "systemtrayicon.h"


FileManager::FileManager(SystemTrayIcon *parent) :
    parent(parent),
    darkenFactor(10)
{
    QObject::connect(this, SIGNAL(canSend()), parent, SLOT(sendSelectedArea()));
    isFileSended = false;
}

bool FileManager::autoSendFile(File const &file)
{
    parent->setIcon(QIcon(":/icon/uploading.png"));

    Uplimg::UploadMethod method = Uplimg::Utils::getUploadMethod();

    if (method == Uplimg::UploadMethod::U_ERROR)
        parent->throwErrorAlert(Uplimg::ErrorList::UPLOAD_METHOD_NOT_CHOOSED);

    if (method == Uplimg::UploadMethod::FTP)
        return sendFileTroughFTP(file);

    else if (method == Uplimg::UploadMethod::HTTP)
        return sendFileTroughHTTP(file);

    else if (method == Uplimg::UploadMethod::UPLIMG_WEB)
        return sendFileTroughUplimgWeb(file);

    else if (method == Uplimg::UploadMethod::LOCAL)
        return true;

    return false;
}

bool FileManager::sendFileTroughFTP(File const &file)
{
    std::unique_ptr<FTPUpload> ftp(new FTPUpload(settings.value(Reg::FTPHost).toString().toStdString(),
                                   settings.value(Reg::FTPPort).toInt(),
                                   settings.value(Reg::FTPUsername).toString().toStdString(),
                                   settings.value(Reg::FTPPassword).toString().toStdString(),
                                   settings.value(Reg::FTPBasePath).toString().toStdString()));

    if (ftp->openConnexion())
        if (ftp->sendFile(file.path.toStdString()))
            if (ftp->closeConnexion())
                return true;

            else std::clog << "FTP module : can't close connection\n";
        else std::clog << "FTP module : can't send file\n";
    else std::clog << "FTP module : can't connect to server\n";

    return false;
}

bool FileManager::sendFileTroughUplimgWeb(File const &file)
{
    HTTPPostUpload * http = new HTTPPostUpload;
    http->setHost(UplimgWeb::host, UplimgWeb::port);
    http->setFile(file.path, UplimgWeb::fileFieldName);
    http->setContentType(file.type);
    http->start();

    sf::Clock clock;

    while(true)
        {
            if(clock.getElapsedTime() >= sf::seconds(30))
                return false;

            sf::sleep(sf::milliseconds(30));

            if(http->canGetReply() && http->reply->isFinished() && http->reply->error() == QNetworkReply::NetworkError::NoError)
                {
                    http->terminate();
                    parent->receivedMessage = QString(http->reply->readAll());
                    http->deleteLater();
                    return true;
                }
            else if(http->canGetReply() && http->reply->isFinished() && http->reply->error() != QNetworkReply::NetworkError::NoError)
                {
                    http->terminate();
                    http->deleteLater();
                    return false;
                }
        }
}

bool FileManager::sendFileTroughHTTP(File const &file)
{
    HTTPPostUpload * http = new HTTPPostUpload;
    http->setHost(settings.value(Reg::HTTPHost).toString(), settings.value(Reg::HTTPPort).toInt());
    http->setFile(file.path, settings.value(Reg::HTTPFileFieldName, "uplimgFile").toString());
    http->setContentType(file.type);
    http->start();

    sf::Clock clock;

    while(true)
        {
            if(clock.getElapsedTime() >= sf::seconds(10))
                return false;

            sf::sleep(sf::milliseconds(30));

            if(http->canGetReply() && http->reply->isFinished() && http->reply->error() == QNetworkReply::NetworkError::NoError)
                {
                    http->terminate();
                    var::lastUrl.setUrl(QString(http->reply->readAll()));
                    http->deleteLater();
                    return true;
                }
            else if(http->canGetReply() && http->reply->isFinished() && http->reply->error() != QNetworkReply::NetworkError::NoError)
                {
                    http->terminate();
                    http->deleteLater();
                    return false;
                }
        }
}

File FileManager::captureSelectedZone(File const &file)
{
    screen = QGuiApplication::primaryScreen();

    this->pathToFile = file.path;

    if (screen)
        {
            originalScreenshot = screen->grabWindow(0);

            if (!originalScreenshot.isNull())
                {
                    fullScreenPicture = new SelectAreaBand(this);
                    fullScreenPicture->setPixmap(originalScreenshot);
                    fullScreenPicture->selectArea();
                }
        }

    return file;
}

void FileManager::areaPictureTaken(QRect area)
{
    originalScreenshot = originalScreenshot.copy(area);

    if(Uplimg::Utils::getImageFormat() == Uplimg::ImageFormat::JPEG)
        originalScreenshot.save(pathToFile, 0, Uplimg::Utils::getImageQuality());
    else if(Uplimg::Utils::getImageFormat() == Uplimg::ImageFormat::PNG)
        originalScreenshot.save(pathToFile, 0, 0);

    emit canSend();
    fullScreenPicture->deleteLater();
}

void FileManager::areaPictureCanceled()
{
    parent->lastActionFinished();
    fullScreenPicture->deleteLater();
    parent->lastActionFinished();
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
    QScreen *screen = QGuiApplication::primaryScreen();
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
    isFileSended = true;
}

void FileManager::pasteReady(const PasteContent &pasteContent)
{
    paste->close();
    paste->deleteLater();
    paste = 0;

    File file;
    file.name = Uplimg::Utils::getNewFileName(".txt");
    file.path = Uplimg::Utils::getFileTempPath(file.name);
    file.type = "paste";
    QFile physicFile(file.path);
    physicFile.open(QIODevice::WriteOnly);
    physicFile.write(pasteContent.fileContent.toLatin1());
    physicFile.close();
    parent->newActionStarted();

    if(autoSendFile(file))
        parent->fileSended(file);
}
