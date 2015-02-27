#ifndef NOTIFICATIONWINDOW_H
#define NOTIFICATIONWINDOW_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQmlContext>
#include <QQuickItem>
#include <QQuickWindow>
#include <QString>
#include <QDesktopServices>
#include <QUrl>
#include <QTimer>

#include "qml/cpp_wrapper/qmlsettings.h"
#include "qml/cpp_wrapper/desktop.h"

class NotificationWindow : public QObject
{
    Q_OBJECT
public:
    explicit NotificationWindow(QString title, QString text, QString link, QObject * parent = 0);
    ~NotificationWindow();

private:
    static short realWindowCount;
    static short relativeWindowCount;

    QString link;

    const short secondsBeforeDelete = 7;
    short secondsElapsed;
    QTimer * deleteTimer;

    QQmlEngine engine;
    QQmlComponent  * component;
    QQmlContext * context;
    QObject * window;

signals:

public slots:
    void show();
    void hide();

    void openLinkAndClose();
};

#endif // NOTIFICATIONWINDOW_H
