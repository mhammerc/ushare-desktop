/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

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

    QFile css(":/design/stylesheet.css");
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
