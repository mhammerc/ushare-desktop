#include <QApplication>
#include <QTranslator>
#include <QFile>
#include <QUrl>

#include "systemtrayicon.h"

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
