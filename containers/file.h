#ifndef FILE_H
#define FILE_H

#include <QString>

class File
{
public:
    File() : realName("undefined"), wantedName("undefined"), path("undefined"), type("undefined")
    {
        hasError = false;

    }

    QString realName; //Name of the file on the disc
    QString wantedName; //Name wanted of the file to download
    QString path;
    QString type;

    bool hasError;

    inline void error()
    {
        hasError = true;
    }
};

#endif // FILE_H
