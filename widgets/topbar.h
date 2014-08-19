#ifndef TOPBAR_H
#define TOPBAR_H

#include <QApplication>
#include <QPoint>
#include <QWidget>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QStyleOption>
#include <QPainter>

class TopBarWidget : public QWidget
{
public:
    TopBarWidget(QWidget * parent): parent(parent) {}

protected:

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
        opt.init (this);
        QPainter p (this);
        style ()->drawPrimitive (QStyle::PE_Widget, &opt, &p, this);
    }

    QPoint dragPosition;
    QWidget * parent;
};

#endif // TOPBAR_H
