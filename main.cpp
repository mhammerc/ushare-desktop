/* Welcome in uShare !! I'm really happy to see you here :-)
 * Don't be scary about comment or edit the code :-P
 * I hope you a good journey in this code :-) *
*/

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

#include <QApplication>
#include <QString>
#include <QUrl>
#include <QFileInfo>
#include <QtQml>
#include <QIcon>

#include "qml/cpp_wrapper/shortcutgetter.h"
#include "ushare.h"


int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    app.setQuitOnLastWindowClosed(false);
    app.setWindowIcon(QIcon(":/images/ushare_icon.png"));

    //qmlRegisterSingletonType(QUrl("qrc:/qml/main_window/global/Global.qml"), "U.Global", 1, 0, "Global");
    qmlRegisterType<ShortcutGetter>("uShare", 0, 1, "ShortcutGetter");

    QCoreApplication::setOrganizationName("uSquare");
    QCoreApplication::setOrganizationDomain("usquare.io");
    QCoreApplication::setApplicationName("uShare");

    /* TRANSLATIONS */

    Settings::init(&app);

    QVariant language = Settings::entry(SettingsKeys::LANGUAGE);

    if(language.isNull())
    {
        QString locale = QLocale::system().name().section('_', 0, 0);
        Settings::setEntry(SettingsKeys::LANGUAGE, locale);
        language = QVariant(locale);
    }


    QTranslator translator;
    translator.load(QString(":/translations/ushare_") + language.toString());
    qApp->installTranslator(&translator);

    /* TRANSLATIONS END */

    uShare uplimg;
    uplimg.start();

    return app.exec();
}
