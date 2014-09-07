/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#ifndef PASTECONTENT_H
#define PASTECONTENT_H

#include <QString>

/* This class store the content of a paste (name and text) designed to transmit it. No logic code, only container. */

class PasteContent
{
public:
    PasteContent():fileTitle("undefined"){}

    QString fileTitle;
    QByteArray fileContentLanguage;
    QString fileContentLanguageHR; //Human readable
    QString fileContent;
};

#endif // PASTECONTENT_H
