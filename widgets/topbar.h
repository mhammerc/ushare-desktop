#ifndef TOPBAR_H
#define TOPBAR_H

#include <QApplication>
#include <QPoint>
#include <QWidget>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>
#include <QHBoxLayout>
#include <QFrame>
#include "shared.h"
#include "button.h"
#include "label.h"

class TopBarWidget : public QFrame
{
    Q_OBJECT
public:
    TopBarWidget(QWidget * parent): parent(parent)
    {
        setContentsMargins(-10,-10,-10,-10);
        layout = new QHBoxLayout;
        icon = new UplimgIcon;
        title = new UplimgTitle("Uplimg");
        minimizeButton = new MinimizeButton;
        closeButton = new CloseButton;

        //--
        layout->addWidget(icon);
        layout->addWidget(title);
        layout->addStretch();
        layout->addWidget(minimizeButton);
        layout->addWidget(closeButton);
        setLayout(layout);

        minimizeButton->setContentsMargins(0,0,0,0);
        closeButton->setContentsMargins(0,0,0,0);
        layout->setSpacing(0);

        QObject::connect(minimizeButton, SIGNAL(clicked()), this, SIGNAL(minimize()));
        QObject::connect(closeButton, SIGNAL(clicked()), this, SIGNAL(close()));
    }

signals:
    void minimize();
    void close();

protected:
    QHBoxLayout * layout;
    UplimgIcon * icon;
    UplimgTitle * title;
    MinimizeButton * minimizeButton;
    CloseButton * closeButton;

    void mousePressEvent(QMouseEvent *event)
    {
        if (event->button() == Qt::LeftButton)
            {
                dragPosition = event->globalPos() - parent->frameGeometry().topLeft();
                event->accept();
            }
    }

    void mouseMoveEvent(QMouseEvent *event)
    {
        if (event->buttons() & Qt::LeftButton)
            {
                parent->move(event->globalPos() - dragPosition);
                event->accept();
            }
    }


    void paintEvent(QPaintEvent *)
    {
        QStyleOption opt;
        opt.init(this);
        QPainter p(this);
        style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
    }

    QPoint dragPosition;
    QWidget * parent;
};

#endif // TOPBAR_H
