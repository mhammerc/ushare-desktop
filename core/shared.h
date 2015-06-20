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
