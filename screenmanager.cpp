#include "screenmanager.h"
#include "systemtrayicon.h"


ScreenManager::ScreenManager(SystemTrayIcon *parent) :
    parent(parent),
    darkenFactor(10)
{
    QObject::connect(this, SIGNAL(canSend()), parent, SLOT(sendSelectedArea()));
    isFileSended = false;
}

bool ScreenManager::autoSendFile(const QString &pathToFile)
{
    parent->setIcon(QIcon(":/icon/uploading.png"));

    Uplimg::UploadMethod method = Uplimg::Utils::getUploadMethod();

    if (method == Uplimg::UploadMethod::ERROR)
        parent->throwErrorAlert(Uplimg::ErrorList::UPLOAD_METHOD_NOT_CHOOSED);

    else if (method == Uplimg::UploadMethod::FTP)
        return sendFileTroughFTP(pathToFile);

    else if (method == Uplimg::UploadMethod::HTTP)
        return sendFileTroughHTTP(pathToFile);

    else if (method == Uplimg::UploadMethod::UPLIMG_WEB)
        return sendFileTroughUplimgWeb(pathToFile);

    else if (method == Uplimg::UploadMethod::LOCAL)
        return true;

    return false;
}

bool ScreenManager::sendFileTroughFTP(const QString &pathToFile)
{
    std::unique_ptr<FTPUpload> ftp(new FTPUpload(settings.value(Reg::FTPHost).toString().toStdString(),
                                   settings.value(Reg::FTPPort).toInt(),
                                   settings.value(Reg::FTPUsername).toString().toStdString(),
                                   settings.value(Reg::FTPPassword).toString().toStdString(),
                                   settings.value(Reg::FTPBasePath).toString().toStdString()));

    if (ftp->openConnexion())
        if (ftp->sendFile(pathToFile.toStdString()))
            if (ftp->closeConnexion())
                return true;

            else std::clog << "can't close\n";
        else std::clog << "can't send\n";
    else std::clog << "can't co\n";

    return false;
}

bool ScreenManager::sendFileTroughUplimgWeb(const QString &pathToFile)
{
    HTTPPostUpload * http = new HTTPPostUpload;
    http->setHost(UplimgWeb::host, UplimgWeb::port);
    http->setFile(pathToFile, UplimgWeb::fileFieldName);
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

bool ScreenManager::sendFileTroughHTTP(const QString &pathToFile)
{
    HTTPPostUpload * http = new HTTPPostUpload;
    http->setHost(settings.value(Reg::HTTPHost).toString(), settings.value(Reg::HTTPPort).toInt());
    http->setFile(pathToFile, settings.value(Reg::HTTPFileFieldName, "uplimgFile").toString());
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
                    parent->lastUrl.setUrl(QString(http->reply->readAll()));
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

QString ScreenManager::captureSelectedZone(const QString &pathToScreen)
{
    //QPixmap fullScreenshot;
    screen = QGuiApplication::primaryScreen();

    this->pathToFile = pathToScreen;

    if (screen)
        {
            originalScreenshot = screen->grabWindow(0);

            if (!originalScreenshot.isNull())
                {
                    //originalScreenshot = fullScreenshot;
                    //fullScreenshot = darkenPicture(fullScreenshot);
                    fullScreenPicture = new SelectAreaBand(this);
                    fullScreenPicture->setPixmap(originalScreenshot);
                    fullScreenPicture->selectArea();
                }
        }

    return pathToScreen;
}

void ScreenManager::areaPictureTaken(QRect area)
{
    originalScreenshot = originalScreenshot.copy(area);

    if(Uplimg::Utils::getImageFormat() == Uplimg::ImageFormat::JPEG)
        originalScreenshot.save(pathToFile, 0, Uplimg::Utils::getImageQuality());
    else if(Uplimg::Utils::getImageFormat() == Uplimg::ImageFormat::PNG)
        originalScreenshot.save(pathToFile, 0, 0);

    emit canSend();
    fullScreenPicture->deleteLater();
}

void ScreenManager::areaPictureCanceled()
{
    parent->lastActionFinished();
    fullScreenPicture->deleteLater();
    parent->lastActionFinished();
}

QPixmap ScreenManager::darkenPicture(const QPixmap &picture)
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

QString ScreenManager::captureFullScreen(const QString &pathToScreen)
{
    QScreen *screen = QGuiApplication::primaryScreen();
    QPixmap screenshot;

    if (screen)
        {
            screenshot = screen->grabWindow(0);

            if(Uplimg::Utils::getImageFormat() == Uplimg::ImageFormat::JPEG)
                {
                    if (!screenshot.save(pathToScreen, 0, Uplimg::Utils::getImageQuality()))
                        return "error";
                }
            else if(Uplimg::Utils::getImageFormat() == Uplimg::ImageFormat::PNG)
                {
                    if (!screenshot.save(pathToScreen, 0, 0))
                        return "error";
                }

            return pathToScreen;
        }

    return "error";

}

ScreenManager::~ScreenManager() {}


void ScreenManager::fileSendedTroughHTTP()
{
    isFileSended = true;
}
