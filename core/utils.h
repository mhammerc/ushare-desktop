#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QTime>
#include <QDate>
#include <QStandardPaths>

class Utils
{
public:

    static QString getNewFileName()
    {
        QTime time = QTime::currentTime();
        QDate date = QDate::currentDate();

        QString fileName = QString::number(date.dayOfYear())
                           + QString::number(time.hour())
                           + QString::number(time.minute())
                           + QString::number(time.second());

        return fileName + ".jpg";
    }

    static QString getFileTempPath(const QString &screenName)
    {
        return QStandardPaths::writableLocation(QStandardPaths::TempLocation)
               + "/"
               + screenName;
    }

};

#endif // UTILS_H

