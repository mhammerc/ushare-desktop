#include "screenmanager.h"
#include "systemtrayicon.h"


ScreenManager::ScreenManager(SystemTrayIcon *parent) :
    choosedMethodSettingName("configuration/method"),
    FTPHostSettingName("configuration/ftp/host"),
    FTPPortSettingName("configuration/ftp/port"),
    FTPUsernameSettingName("configuration/ftp/username"),
    FTPPasswordSettingName("configuration/ftp/password"),
    FTPBasePathSettingName("configuration/ftp/basePath"),
    HTTPHostSettingName("configuration/http/host"),
    HTTPPortSettingName("configuration/http/port"),
    HTTPFileFieldNameSettingName("configuration/http/fieldName"),
    darkenFactor(40),
    parent(parent)
{
    QObject::connect(this, SIGNAL(canSend()), parent, SLOT(sendSelectedArea()));
    isFileSended = false;
}

bool ScreenManager::autoSendFile(const QString &pathToFile)
{
    Uplimg::UploadMethod method = parent->getUploadMethod();

    if (method == Uplimg::UploadMethod::ERROR)
        parent->throwErrorAlert(Uplimg::ErrorList::UPLOAD_METHOD_NOT_CHOOSED);

    else if (method == Uplimg::UploadMethod::FTP)
        return sendFileTroughFTP(pathToFile);

    else if (method == Uplimg::UploadMethod::HTTP)
        return sendFileTroughHTTP(pathToFile);

    return false;
}

bool ScreenManager::sendFileTroughFTP(const QString &pathToFile)
{
    std::unique_ptr<FTPUpload> ftp(new FTPUpload(settings.value(FTPHostSettingName).toString().toStdString(),
                                   settings.value(FTPPortSettingName).toInt(),
                                   settings.value(FTPUsernameSettingName).toString().toStdString(),
                                   settings.value(FTPPasswordSettingName).toString().toStdString(),
                                   settings.value(FTPBasePathSettingName).toString().toStdString()));

    if (ftp->openConnexion())
        if (ftp->sendFile(pathToFile.toStdString()))
            if (ftp->closeConnexion())
                return true;

            else std::clog << "can't close\n";
        else std::clog << "can't send\n";
    else std::clog << "can't co\n";

    return false;
}

bool ScreenManager::sendFileTroughHTTP(const QString &pathToFile)
{
    HTTPPostUpload * http = new HTTPPostUpload;
    http->setHost(settings.value(HTTPHostSettingName).toString(), settings.value(HTTPPortSettingName).toInt());
    http->setFile(pathToFile, settings.value(HTTPFileFieldNameSettingName, "uplimgFile").toString());
    http->setContentType("image/png");
    http->start();

    while(true)
        {
            sf::sleep(sf::milliseconds(1000));
            if(http->canGetReply() && http->reply->isFinished())
                {
                    http->terminate();
                    http->deleteLater();
                    //delete http;
                    return true;
                }
        }
}

QString ScreenManager::captureSelectedZone(const QString &pathToScreen)
{

    QScreen * screen = QGuiApplication::primaryScreen();
    this->pathToFile = pathToScreen;
    QPixmap fullScreenshot;

    if (screen)
        {
            fullScreenshot = screen->grabWindow(0);

            if (!fullScreenshot.isNull())
                {
                    originalScreenshot = fullScreenshot;
                    fullScreenshot = darkenPicture(fullScreenshot);
                    SelectAreaBand * fullScreenPicture = new SelectAreaBand(this);
                    fullScreenPicture->setPixmap(fullScreenshot);
                    fullScreenPicture->selectArea();
                }
        }

    return pathToScreen;
}

void ScreenManager::areaPictureTaken(QRect area)
{
    originalScreenshot = originalScreenshot.copy(area);
    originalScreenshot.save(pathToFile);
    emit canSend();
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

            if (!screenshot.save(pathToScreen, 0, 0))
                return "error";

            return pathToScreen;
        }

    return "error";

}

ScreenManager::~ScreenManager() {}


void ScreenManager::fileSendedTroughHTTP()
{
    isFileSended = true;
}
