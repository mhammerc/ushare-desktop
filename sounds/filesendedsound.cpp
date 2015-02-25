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
