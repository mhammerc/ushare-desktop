/* Welcome in USquare !! I'm really happy to see you here :-)
 * Don't be scary about comment or edit the code :-P
 * I hope you a good journey in this code :-) *
*/

/**
 * This file (c) by : - Martin Hammerchmidt alias Imote
 *
 * This file is licensed under a
 * Creative Commons Attribution-NonCommercial-ShareAlike 4.0
 * International License.
 *
 * You should have received a copy of the license along with this
 * work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.
 *
 * If you have contributed to this file, add your name to authors list.
*/

#include <QApplication>
#include <QString>
#include <QUrl>
#include <QFileInfo>
#include <QtQml>
#include "uplimg.h"

//#include "core/settings.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setQuitOnLastWindowClosed(false);

    const QString location = "qml/main_window/global/Global.qml";
    QUrl singleton = QUrl::fromLocalFile(QFileInfo(location).absoluteFilePath());
    qmlRegisterSingletonType(singleton, "U.Global", 1, 0, "Global");

    QCoreApplication::setOrganizationName("uSquare");
    QCoreApplication::setOrganizationDomain("usquare.io");
    QCoreApplication::setApplicationName("uShare");

    /* TRANSLATIONS */

    Settings::init(&app);

    QVariant language = Settings::entry(SettingsKeys::LANGUAGE);
    qDebug() << QString("ushare_") + language.toString();

    if(language.isNull())
    {
        QString locale = QLocale::system().name().section('_', 0, 0);
        Settings::setEntry(SettingsKeys::LANGUAGE, locale);
        language = QVariant(locale);
    }


    QTranslator translator;
    qDebug() << translator.load(QString("ushare_") + language.toString());
    qDebug() << qApp->installTranslator(&translator);

    /* TRANSLATIONS END */

    Uplimg uplimg;
    uplimg.start();

    return app.exec();
}
