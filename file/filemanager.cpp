#include "filemanager.h"

FileManager::FileManager(QObject *parent) : QObject(parent)
{

}

FileManager::~FileManager()
{

}

void FileManager::screenTook(QPixmap picture)
{
    /* Assuming that we send the picture to uplimg web */
    QString filename = Utils::getNewFileName();
    QString filePath = Utils::getFolderPath(filename);

    int quality = Settings::entry(SettingsKeys::IMAGE_QUALITY, 100).toInt();
    int format = Settings::entry(SettingsKeys::IMAGE_FORMAT, false).toBool(); // 0 -> JPEG | 1 -> PNG

    if(!picture.save(filePath, 0, format ? 0 : quality))
    {
        /* get back to idle state */
        return;
    }

    File file;
    file.filename = filename;
    file.path = filePath;
    file.type = "screen";

    emit fileReadyToBeSent(file);
}

void FileManager::chooseFile()
{
    /* assume that we want to send it */
    QString fileName = QFileDialog::getOpenFileName();

    QFileInfo fileInfo(fileName);

    File file;
    file.filename = fileInfo.fileName();
    file.path = fileInfo.filePath();
    file.type = "file";

    emit fileReadyToBeSent(file);

}

