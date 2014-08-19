#ifndef PASTECONTENT_H
#define PASTECONTENT_H

#include <QString>

/* This class store the content of a paste (name and text) designed to transmit it. No logic code, only container. */

class PasteContent
{
public:
    PasteContent(){}

    QString fileTitle;
    QString fileContent;
};

#endif // PASTECONTENT_H
