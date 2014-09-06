/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

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
