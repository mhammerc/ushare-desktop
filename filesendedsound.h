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
    QString const fileSendedSoundOne;
    QString const fileSendedSoundTwo; //Easter egg
    QSound * sound;
};

#endif // FILESENDEDSOUND_H
