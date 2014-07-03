/**
  This file simply represent the area band when selecting area for take screen.
 */

#ifndef SELECTAREABAND_H
#define SELECTAREABAND_H

#include <QRubberBand>
#include <QWidget>
#include <QMouseEvent>
#include <QLabel>
#include <QPoint>
#include <QRect>
#include <QPoint>
#include <QCursor>

class ScreenManager;

class SelectAreaBand : public QLabel
{
    Q_OBJECT
public:
    SelectAreaBand(ScreenManager * manager, QWidget * parent = 0);
    virtual ~SelectAreaBand();

    void selectArea();

protected:
    QRubberBand * rubberBand;
    QPoint origin;
    ScreenManager * manager;

    virtual void mousePressEvent(QMouseEvent * event);
    virtual void mouseMoveEvent(QMouseEvent * event);
    virtual void mouseReleaseEvent(QMouseEvent * event);


signals:
    void areaTaken(QRect);
};

#endif // SELECTAREABAND_H
