#ifndef SHARED_H
#define SHARED_H

#include <QObject>
#include <QString>

class Shared : public QObject
{
    Q_OBJECT
public:
    const static QString appVersion;
    const static int uploadPort;

    const static int globalPort;

    const static QString uploadUrl;
    const static QString deleteUrl;
    const static QString editPasswordUrl;
    const static QString authUrl;
    const static QString registerUrl;
    const static QString wsUrl;
    const static QString silentViewUrl;
    const static QString updateInfoUrl;
    const static QString domainName;

};

#endif // SHARED_H
