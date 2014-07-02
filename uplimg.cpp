#include <QApplication>
#include <QTranslator>
#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QList>
#include "systemtrayicon.h"
#include "configuration/configurationwindows.h"

#include <QHttpMultiPart>
#include <QHttpPart>
#include <QNetworkRequest>
#include <QUrl>
#include <QFile>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <fstream>

#include <iostream>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    QCoreApplication::setOrganizationName("ImoteSystem");
    QCoreApplication::setApplicationName("Uplimg");

    SystemTrayIcon systemTray;

    //QWidget fuckU;
    return app.exec();
}
