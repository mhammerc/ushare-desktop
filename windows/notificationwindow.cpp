#include "notificationwindow.h"

short NotificationWindow::realWindowCount = 0;
short NotificationWindow::relativeWindowCount = 0;

NotificationWindow::NotificationWindow(QString title, QString text, QString link, QObject *parent)
    : QObject(parent),
      link(link)
{
    component = new QQmlComponent(&engine, QUrl::fromLocalFile("qml/notification_window/NotificationWindow.qml"), this);

    context = new QQmlContext(&engine);

    QmlSettings * settings = new QmlSettings(this);
    context->setContextProperty("Settings", settings);

    QmlDesktop * desktop = new QmlDesktop(this);
    context->setContextProperty("Desktop", desktop);

    window = component->create(context);
    qDebug() << component->errorString();

    window->setProperty("title", title);
    window->setProperty("text", text);

    QObject::connect(window, SIGNAL(closeAsked()), this, SLOT(deleteLater()));

    QObject::connect(window, SIGNAL(clickedInWindow()), this, SLOT(openLinkAndClose()));
}

void NotificationWindow::show()
{
    window->setProperty("count", secondsBeforeDelete);

    ++realWindowCount;
    ++relativeWindowCount;

    window->setProperty("windowCount", relativeWindowCount);
    window->setProperty("visible", true);

    deleteTimer = new QTimer(this);
    secondsElapsed = 0;

    QObject::connect(deleteTimer, &QTimer::timeout, [this](){
        ++secondsElapsed;

        if(secondsElapsed == secondsBeforeDelete)
            deleteLater();
        else
            window->setProperty("count", secondsBeforeDelete - secondsElapsed);
    });

    deleteTimer->start(1000);
}

void NotificationWindow::hide()
{
    window->setProperty("visible", false);
}

void NotificationWindow::openLinkAndClose()
{
    QDesktopServices::openUrl(QUrl(link));
    deleteLater();
}

NotificationWindow::~NotificationWindow()
{
    --realWindowCount;
    if(realWindowCount == 0)
        relativeWindowCount = 0;

    window->deleteLater();
}

