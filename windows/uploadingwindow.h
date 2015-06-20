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

#ifndef UPLOADINGWINDOW_H
#define UPLOADINGWINDOW_H

#include <QObject>
#include "qmlengine.h"
#include <QQmlComponent>
#include <QQuickItem>
#include <QQuickWindow>
#include <QQmlContext>

#include "qml/cpp_wrapper/desktop.h"

class UploadingWindow : public QObject
{
    Q_OBJECT
public:
    explicit UploadingWindow(QObject *parent = 0);
    ~UploadingWindow();

private:
    QmlEngine engine;
    QQmlComponent  * component;
    QQmlContext * context;
    QObject * window;

signals:
    void cancellationAsked();

public slots:
    void show();
    void hide();
    void setProgress(float);
    void setBytesTotal(qint64);
};

#endif // UPLOADINGWINDOW_H
