#ifndef SCREENTAKER_H
#define SCREENTAKER_H


#include <QObject>
#include <QGuiApplication>
#include <QPixmap>
#include <QScreen>

#include "core/areauserdefiner.h"

class ScreenTaker : public QObject
{
    Q_OBJECT
public:
    explicit ScreenTaker(QObject * parent = 0);

    QPixmap captureFullScreen();
    bool captureSelectedZone(QColor areaColor);
    //QPixmap captureSpecificWindow(); -> not implemented yet

signals:
    void captureSelectedZoneFinished(QPixmap);
    void captureSelectedZoneCanceled();

public slots:
};

#endif // SCREENTAKER_H
