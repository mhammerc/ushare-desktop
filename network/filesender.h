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
