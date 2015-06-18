#ifndef SHARED_H
#define SHARED_H

#include <QObject>
#include <QString>

class Shared : public QObject
{
    Q_OBJECT
public:
    const static QString appVersion;

    const static int globalPort;

    const static QString domainName;

    const static QString updateInfoUrl;
    const static QString uploadUrl;
    const static QString silentViewUrl;
    const static QString authUrl;
    const static QString registerUrl;
    const static QString getUserInfo;
    const static QString getUploadList;
    const static QString editPasswordUrl;
    const static QString deleteUrl;

};

#endif // SHARED_H
