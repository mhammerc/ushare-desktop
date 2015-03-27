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
    const static QString url;

    const static int globalPort;

    const static QString uploadUrl;
    const static QString authUrl;
    const static QString registerUrl;
    const static QString wsUrl;
    const static QString silentViewUrl;
    const static QString domainName;

};

#endif // SHARED_H
