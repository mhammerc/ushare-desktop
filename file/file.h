#ifndef FILE_H
#define FILE_H

#include <QString>

class File
{
public:
    File()
    {

    }

    QString filename; // Name of the file on the hard drive
    QString wantedFilename; // Name of the file wanted on the web
    QString path; // Path of the file on the hard drive

    /* Paste specific */
    QByteArray language;
    QString humanReadableLanguage;

    bool hasError;

    inline void error()
    {
        hasError = true;
    }
};

#endif // FILE_H

