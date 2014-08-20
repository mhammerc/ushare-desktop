#include "filesendedsound.h"

FileSendedSound::FileSendedSound(QObject * parent) :
    QObject(parent), fileSendedSoundOne(":/fileSended.wav"), fileSendedSoundTwo(":/Easter_Egg.wav"), sound(new QSound(fileSendedSoundOne, parent)), easterEggActivated(false)
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
        sound = new QSound(fileSendedSoundTwo, parent());
    }
}

void FileSendedSound::play()
{
    sound->play();
}
