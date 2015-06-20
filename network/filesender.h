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

#ifndef FILESENDER_H
#define FILESENDER_H

#include <QObject>
#include <QString>
#include <QFileInfo>

#include "file/file.h"
#include "httpsender.h"
#include "windows/uploadingwindow.h"

#include "core/settings.h"
#include "core/shared.h"

class FileSender : public QObject
{
    Q_OBJECT
public:
    explicit FileSender(QObject *parent = 0);
    ~FileSender();

private:
    HttpSender http;

    UploadingWindow * uploadingWindow;

    QMetaObject::Connection uploadFinishedConnection;

signals:
    void uploadFinished(QString);

public slots:
    void autoSendFile(File);
    void cancelUpload();
    void cancelFinished();
};

#endif // FILESENDER_H
