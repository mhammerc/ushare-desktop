/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

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
