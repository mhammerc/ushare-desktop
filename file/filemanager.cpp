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

    if(fileName == "") return;

    QFileInfo fileInfo(fileName);

    File file;
    file.filename = fileInfo.fileName();
    file.path = fileInfo.filePath();
    file.type = "file";

    emit fileReadyToBeSent(file);

}

void FileManager::sendClipboard()
{
    QClipboard * clipboard = QApplication::clipboard();

    QString filePath = "";

#ifdef __linux__ /* When copying a file in clipboard, linux store the path of the file inside the clipboard.*/

    filePath = clipboard->text();

#elif _WIN32 /* When copying a file in clipboard, Windows store the path of the file with 'file:///' at the beginning of the path. */

    filePath = clipboard->text();
    filePath = clipboardFileName.right(clipboardFileName.size() - 8);

#endif /* TODO: Support MAC */

    if(!QFile::exists(filePath))
    {
        QString filename = Utils::getNewFileName(".txt");
        filePath = Utils::getFolderPath(filename);

        QFile file(filePath);

        if(file.open(QIODevice::ReadWrite))
        {
            QTextStream stream(&file);
            stream << clipboard->text();
        }

        file.close();
    }

    QFileInfo fileInfo(filePath);
    File file;
    file.filename = fileInfo.fileName();
    file.path = fileInfo.filePath();

    emit fileReadyToBeSent(file);
}

