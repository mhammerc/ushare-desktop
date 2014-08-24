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
    parent->setIcon(QIcon(":/icon/uploading.png"));
    lastFile = file;
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
        return;

    return;
}

void FileManager::sendFileTroughFTP(File const &file)
{
    ftp = new FTPUpload(file,
                        settings.value(Reg::FTPHost).toString(),
                        settings.value(Reg::FTPPort).toInt(),
                        settings.value(Reg::FTPUsername).toString(),
                        settings.value(Reg::FTPPassword).toString(),
                        settings.value(Reg::FTPBasePath).toString(),
                        this);

    QObject::connect(ftp, SIGNAL(operationFinished()), this, SLOT(fileSendedTroughFTP()));
    ftp->run();

//    if (ftp->openConnexion())
//        if (ftp->sendFile(file.path.toStdString()))
//            if (ftp->closeConnexion())
//                return;

//            else std::clog << "FTP module : can't close connection\n";
//        else std::clog << "FTP module : can't send file\n";
//    else std::clog << "FTP module : can't connect to server\n";

}

void FileManager::sendFileTroughUplimgWeb(File const &file)
{
    http = new HTTPPostUpload(this);
    http->setHost(UplimgWeb::host, UplimgWeb::port);
    http->setFile(file.path, UplimgWeb::fileFieldName);
    http->setContentType(file.type);
    http->start();
}

void FileManager::sendFileTroughHTTP(File const &file)
{
    http = new HTTPPostUpload(this);
    http->setHost(settings.value(Reg::HTTPHost).toString(), settings.value(Reg::HTTPPort).toInt());
    http->setFile(file.path, settings.value(Reg::HTTPFileFieldName, "uplimgFile").toString());
    http->setContentType(file.type);
    http->start();
}

File FileManager::captureSelectedZone(File const &file)
{
    screen = QGuiApplication::primaryScreen();

    this->lastFile = file;

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
        originalScreenshot.save(lastFile.path, 0, Uplimg::Utils::getImageQuality());
    else if(Uplimg::Utils::getImageFormat() == Uplimg::ImageFormat::PNG)
        originalScreenshot.save(lastFile.path, 0, 0);

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
    if(http->reply->error() == QNetworkReply::NetworkError::NoError)
        {
            http->terminate();
            var::lastUrl.setUrl(QString(http->reply->readAll()));
            http->deleteLater();
            http = nullptr;
            parent->fileSended(lastFile);

        }
    else if(http->reply->error() != QNetworkReply::NetworkError::NoError)
        {
            http->terminate();
            http->deleteLater();
            http = nullptr;
            parent->throwErrorAlert(Uplimg::UPLOAD_FAIL);
        }

}

void FileManager::fileSendedTroughFTP()
{
    if(ftp->status == Uplimg::FTP_SUCCESS)
        {
            ftp->terminate();
            ftp->deleteLater();
            ftp = nullptr;
            parent->fileSended(lastFile);
        }
    else if(ftp->status == Uplimg::FTP_UNKNOWN_ERROR || ftp->status == Uplimg::FTP_CANT_CONNECT)
        {
            ftp->terminate();
            ftp->deleteLater();
            ftp = nullptr;
            parent->throwErrorAlert(Uplimg::UPLOAD_FAIL);
        }
}

void FileManager::pasteReady(const PasteContent &pasteContent)
{
    paste->close();
    paste->deleteLater();
    paste = nullptr;

    File file;
    file.name = Uplimg::Utils::getNewFileName(".txt");
    file.path = Uplimg::Utils::getFileTempPath(file.name);
    file.type = "paste";
    QFile physicFile(file.path);
    physicFile.open(QIODevice::WriteOnly);
    physicFile.write(pasteContent.fileContent.toLatin1());
    physicFile.close();
    parent->newActionStarted();
    autoSendFile(file);
}
