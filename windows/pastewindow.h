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

#ifndef PASTEWINDOW_H
#define PASTEWINDOW_H

#include <QObject>
#include "qmlengine.h"
#include <QQmlComponent>
#include <QQuickItem>
#include <QQuickWindow>

class PasteWindow : public QObject
{
    Q_OBJECT
public:
    explicit PasteWindow(QObject * parent = 0);
    ~PasteWindow();

public slots:
    void newPaste();
    void cancelPaste();

private slots:
    void _pasteReady(QString name, QString content);

private:
    void deletePasteWindow();

signals:
    void pasteReady(QString filename, QString content);

private:
    QmlEngine engine;
    QQmlComponent * component;
    QObject * window;

};

#endif // PASTEWINDOW_H
