/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#include "notificationwindow.h"
#include "systemtrayicon.h"

NotificationWindow::NotificationWindow(QString const &title, QString const &message, SystemTrayIcon * systray, QWidget *parent, Qt::WindowFlags f) : QWidget(parent, Qt::WindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowSystemMenuHint | Qt::WindowStaysOnTopHint)), parent(systray), message(message), title(title)
{
    Q_UNUSED(f);

    setAttribute(Qt::WA_TranslucentBackground, true);
    setAttribute(Qt::WA_DeleteOnClose, true);
    setContentsMargins(-10,-10,-10,-10);
    resize(200,80);

    setUpUI();

    timeToShowWindow = new QTimer(this);
    timeToShowWindow->setSingleShot(true);
    timeToShowWindow->setInterval(10000);

    QObject::connect(closeButton, SIGNAL(clicked()), this, SLOT(close()));
    QObject::connect(timeToShowWindow, SIGNAL(timeout()), this, SLOT(close()));

    timeToShowWindow->start();
    show();

    /* To move the notification at bottom right corner */
    QDesktopWidget desktop;
    QRect geometryDesktop = desktop.screenGeometry();
    move(geometryDesktop.bottomRight().x() - this->width() - 15, geometryDesktop.bottomRight().y() - this->height() - 75);
}

void NotificationWindow::setUpUI()
{
    widget = new QWidget;
    widget->setObjectName("NotificationContent");
    mainLayout = new QVBoxLayout;
    layout = new QVBoxLayout;

    titleLabel = new QLabel(title);
    titleLabel->setObjectName("NotificationTitle");
    closeButton = new QPushButton;
    closeButton->setObjectName("NotificationCloseButton");
    topLayout = new QHBoxLayout;
    topLayout->addWidget(titleLabel);
    topLayout->addStretch();
    topLayout->addWidget(closeButton);

    messageLabel = new QLabel(message);
    messageLabel->setObjectName("NotificationMessage");

    layout->addLayout(topLayout);
    layout->addWidget(messageLabel);
    layout->addStretch();
    widget->setLayout(layout);
    mainLayout->addWidget(widget);
    setLayout(mainLayout);
}

void NotificationWindow::mousePressEvent(QMouseEvent *event)
{
    if(event->button() != Qt::LeftButton)
        return;

    parent->openLastUrl();
    this->close();
}
