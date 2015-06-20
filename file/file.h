/**
 * This file (c) by : - Martin Hammerchmidt alias Imote
 *
 * This file is licensed under a
 * GNU GENERAL PUBLIC LICENSE V3.0
 *
 * See the LICENSE file to learn more.
 *
 * If you have contributed to this file, add your name to authors list.
*/

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

