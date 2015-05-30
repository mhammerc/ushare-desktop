#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <QObject>
#include <QPixmap>
#include <QFileDialog>
#include <QFileInfo>
#include <QClipboard>
#include <QApplication>

#include "core/settings.h"
#include "file.h"

#include <iostream>

#include "core/utils.h"

class FileManager : public QObject
{
    Q_OBJECT
public:
    explicit FileManager(QObject *parent = 0);
    ~FileManager();

signals:
    void fileReadyToBeSent(File);

public slots:
    void screenTook(QPixmap);

    void chooseFile();

    void sendClipboard();

    void sendDatas(QString filename, QString content);

    void sendFile(QString &filename);
};

#endif // FILEMANAGER_H
