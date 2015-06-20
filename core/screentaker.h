/**
 * This file (c) by : - Martin Hammerchmidt alias Imote
 *
 * This file is licensed under a
 * GNU GENERAL PUBLIC LICENSE V3.0
 *
 * See the LICENSE file to learn more.
 *
 * If you have contributed to this file, add your name to authors list.
*/

#ifndef SCREENTAKER_H
#define SCREENTAKER_H

#include <QApplication>
#include <QObject>
#include <QGuiApplication>
#include <QPixmap>
#include <QScreen>
#include <QDebug>

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
