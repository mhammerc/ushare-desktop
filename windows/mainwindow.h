#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QDebug>

#include "qml/cpp_wrapper/qmlsettings.h"
#include "qml/cpp_wrapper/platformdetails.h"
#include "qml/cpp_wrapper/clipboard.h"
#include "qml/cpp_wrapper/desktop.h"

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = 0);
    ~MainWindow();

private:
    QQmlEngine engine;
    QQmlComponent  * component;
    QQmlContext * context;
    QObject * window;

signals:

public slots:
    void show();
    void hide();
};

#endif // MAINWINDOW_H
