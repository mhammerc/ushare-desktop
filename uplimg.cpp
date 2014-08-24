#include <QApplication>
#include <QTranslator>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QList>
#include <QObject>
#include "systemtrayicon.h"

#include <QHttpMultiPart>
#include <QHttpPart>
#include <QNetworkRequest>
#include <QUrl>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QSignalMapper>
#include <QString>
#include <thread>
#include <chrono>

#include <QStyleFactory>
#include <QStringList>

#include "shared.h"

#include <fstream>

#include <iostream>

QUrl var::lastUrl;

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    app.setQuitOnLastWindowClosed(false);
    QCoreApplication::setOrganizationName("Uplimg corporation");
    QCoreApplication::setApplicationName(Uplimg::applicationName);

    QFile css("styleSheet.css");
    css.open(QIODevice::ReadOnly);
    QString sheet(css.readAll());
    app.setStyleSheet(sheet);

    QTranslator translator;

    const QString langSettingName("configuration/lang");
    QSettings settings;

    if(settings.value(langSettingName).toString() == "English")
        translator.load(":/lang/uplimg_en");
    else if(settings.value(langSettingName).toString() == "Français")
        translator.load(":/lang/uplimg_fr");
    else
        {
            QString locale = QLocale::system().name().section('_', 0, 0);
            translator.load(QString(":/lang/uplimg_") + locale);
        }

    app.installTranslator(&translator);

    SystemTrayIcon systemTray;
    systemTray.show();
    systemTray.setVisible(true);

    return app.exec();
}
