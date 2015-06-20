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

#include "filesendedsound.h"

FileSendedSound::FileSendedSound(QObject * parent) :
    QObject(parent),
    easterEggActivated(false),
    sound(new QSound(fileSendedSoundOne, this))
{}

FileSendedSound::~FileSendedSound()
{
    sound->deleteLater();
}

void FileSendedSound::enableEasterEgg()
{
    if(!easterEggActivated)
    {
        easterEggActivated = true;
        sound->deleteLater();
        sound = new QSound(fileSendedSoundTwo, this);
    }
}

void FileSendedSound::play()
{
    sound->play();
}
