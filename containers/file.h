#ifndef FILE_H
#define FILE_H

#include <QString>

class File
{
public:
    File()
    {
        hasError = false;
    }

    QString name;
    QString path;
    QString type;

    bool hasError;

    inline void error()
    {
        hasError = true;
    }
};

#endif // FILE_H
