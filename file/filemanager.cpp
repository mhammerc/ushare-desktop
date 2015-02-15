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
    QString filePath = Utils::getFileTempPath(filename);

    if(!picture.save(filePath))
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

