#include "selectareaband.h"
#include "screenmanager.h"


SelectAreaBand::SelectAreaBand(ScreenManager *manager, QWidget * parent) : QLabel(parent)
{
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    this->manager = manager;
    QObject::connect(this, SIGNAL(areaTaken(QRect)), manager, SLOT(areaPictureTaken(QRect)));
}

void SelectAreaBand::selectArea()
{
    showFullScreen();
}

void SelectAreaBand::mousePressEvent(QMouseEvent * event)
{
    origin = event->pos();
    rubberBand->setGeometry(QRect(origin, QSize(10,10)));
    rubberBand->show();
}

void SelectAreaBand::mouseMoveEvent(QMouseEvent * event)
{
    rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
}

void SelectAreaBand::mouseReleaseEvent(QMouseEvent * event)
{
    rubberBand->hide();
    this->hide();
    emit areaTaken(QRect(origin, event->pos()).normalized());
}

SelectAreaBand::~SelectAreaBand() {}
