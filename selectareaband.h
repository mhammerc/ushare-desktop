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
#include <QPalette>
#include <cstdlib>
#include <ctime>

#include "shared.h"

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
    virtual void keyPressEvent(QKeyEvent *);


signals:
    void areaTaken(QRect);
    void areaCanceled();
};

#endif // SELECTAREABAND_H
