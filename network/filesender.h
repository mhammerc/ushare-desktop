#ifndef FILESENDER_H
#define FILESENDER_H

#include <QObject>

#include <file/file.h>
#include "httpsender.h"

#include <iostream>

class FileSender : public QObject
{
    Q_OBJECT
public:
    explicit FileSender(QObject *parent = 0);
    ~FileSender();

signals:

public slots:
    void autoSendFile(File);
};

#endif // FILESENDER_H
