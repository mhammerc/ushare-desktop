#ifndef NOTIFICATIONWINDOW_H
#define NOTIFICATIONWINDOW_H

#include <QFrame>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QPaintEvent>
#include <QStyleOption>
#include <QPainter>
#include <QWidget>
#include <QTimer>
#include <QDesktopWidget>
#include <QRect>

#include "shared.h"

class SystemTrayIcon;

class NotificationWindow : public QWidget
{
    Q_OBJECT
public:
    NotificationWindow(QString const &title, QString const &message, SystemTrayIcon * systray, QWidget * parent = 0, Qt::WindowFlags f = 0);

    void paintEvent(QPaintEvent *)
    {
        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }

protected:
    void setUpUI();
    virtual void mousePressEvent(QMouseEvent * event);

    SystemTrayIcon * parent;
    QString message;
    QString title;
    QTimer * timeToShowWindow;

    //Layout
    QVBoxLayout * mainLayout;
    QWidget * widget;
    QVBoxLayout * layout;

    QHBoxLayout * topLayout;
    QLabel * titleLabel;
    QPushButton * closeButton;

    QLabel * messageLabel;
};
#endif // NOTIFICATIONWINDOW_H
