/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

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
