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

#ifndef FILESENDEDSOUND_H
#define FILESENDEDSOUND_H

#include <QApplication>
#include <QSound>

class FileSendedSound : public QObject
{
    Q_OBJECT
public:
    explicit FileSendedSound(QObject * parent = 0);
    ~FileSendedSound();

public slots:
    void enableEasterEgg();
    void play();

protected:
    bool easterEggActivated;
    QString const fileSendedSoundOne = QString(":/sounds/file_sended.wav");
    QString const fileSendedSoundTwo = QString(":/sounds/easter_egg.wav"); // Easter egg
    QSound * sound;
};

#endif // FILESENDEDSOUND_H
