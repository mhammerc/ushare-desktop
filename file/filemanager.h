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
