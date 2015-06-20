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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include "qmlengine.h"
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>

#include "core/shared.h"
#include "core/systemtrayicon.h"

#include "qml/cpp_wrapper/qmlsettings.h"
#include "qml/cpp_wrapper/clipboard.h"
#include "qml/cpp_wrapper/desktop.h"
#include "qml/cpp_wrapper/ushareonline.h"
#include "qml/cpp_wrapper/shortcuts.h"

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(SystemTrayIcon * systemTrayIcon, QObject * parent = 0);
    ~MainWindow();

private:
    QmlEngine engine;
    QQmlComponent  * component;
    QQmlContext * context;
    QObject * window;

signals:

public slots:
    void show();
    void hide();
};

#endif // MAINWINDOW_H
