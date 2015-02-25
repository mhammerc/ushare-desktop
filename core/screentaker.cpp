#include "screentaker.h"

ScreenTaker::ScreenTaker(QObject *parent) : QObject(parent){}

QPixmap ScreenTaker::captureFullScreen()
{
    QScreen * screen = QGuiApplication::primaryScreen();
    if(!screen) return QPixmap();
    return screen->grabWindow(0);
}

/* Windows, Mac and Linux don't work the same way FIXME: only linux implemented at the moment */

#ifdef _WIN32
bool ScreenTaker::captureSelectedZone(QColor areaColor)
{
    QScreen * screen = QGuiApplication::screens()[0];
    if(!screen) return false;

    QRect vg = screen->virtualGeometry(); // vg -> virtual geometry
    QPixmap capture = screen->grabWindow(0, vg.x(), vg.y(), vg.width(), vg.height());
    if(capture.isNull()) return false;

    AreaUserDefiner * area = new AreaUserDefiner(areaColor);
    area->setPixmap(capture);
    area->setGeometry(vg);

    QObject::connect(area, &AreaUserDefiner::areaTaken, [capture, area, this](QRect areaSelected)
        {
            QPixmap finalCapture = capture.copy(areaSelected);
            emit captureSelectedZoneFinished(finalCapture);
            area->deleteLater();
        });

    QObject::connect(area, &AreaUserDefiner::areaCanceled, this, &ScreenTaker::captureSelectedZoneCanceled);
    QObject::connect(area, &AreaUserDefiner::areaCanceled, area, &AreaUserDefiner::deleteLater);

    area->start();

    return true;
}
#endif

#ifdef __linux__
bool ScreenTaker::captureSelectedZone(QColor areaColor)
{
    QScreen * screen = QApplication::primaryScreen();
    if(!screen) return false;

    QPixmap capture = screen->grabWindow(0);
    if(capture.isNull()) return false;

    AreaUserDefiner * area = new AreaUserDefiner(areaColor);
    area->setPixmap(capture);

    QObject::connect(area, &AreaUserDefiner::areaTaken, [capture, area, this](QRect areaSelected)
        {
            QPixmap finalCapture = capture.copy(areaSelected);
            emit captureSelectedZoneFinished(finalCapture);
            area->deleteLater();
        });

    QObject::connect(area, &AreaUserDefiner::areaCanceled, this, &ScreenTaker::captureSelectedZoneCanceled);
    QObject::connect(area, &AreaUserDefiner::areaCanceled, area, &AreaUserDefiner::deleteLater);

    area->start();

    return true;
}
#endif
