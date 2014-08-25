#include "selectareaband.h"
#include "screenmanager.h"


SelectAreaBand::SelectAreaBand(FileManager *manager, QWidget * parent) :
    QLabel(parent)
{
    QSettings settings;
    QColor color;

    if(settings.value(Reg::randomizeArea).toBool())
        {
            std::srand(std::time(0));
            color.setRed(std::rand()%255);
            color.setGreen(std::rand()%255);
            color.setBlue(std::rand()%255);
        }
    else
        {
            color.setRed(settings.value(Reg::redArea).toInt());
            color.setGreen(settings.value(Reg::greenArea).toInt());
            color.setBlue(settings.value(Reg::blueArea).toInt());
        }

    setCursor(Qt::CrossCursor);
    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);
    this->manager = manager;

    QObject::connect(this, SIGNAL(areaTaken(QRect)), manager, SLOT(areaPictureTaken(QRect)));
    QObject::connect(this, SIGNAL(areaCanceled()), manager, SLOT(areaPictureCanceled()));

    QPalette palette;
    palette.setColor(QPalette::Normal, QPalette::Highlight, color);
    setPalette(palette);
    rubberBand->setPalette(palette);
}

void SelectAreaBand::selectArea()
{
    showFullScreen();
}

void SelectAreaBand::mousePressEvent(QMouseEvent * event)
{
    if(event->button() != Qt::LeftButton)
        return;

    origin = event->pos();
    rubberBand->setGeometry(QRect(origin, QSize(0,0)));
    rubberBand->show();
}

void SelectAreaBand::mouseMoveEvent(QMouseEvent * event)
{
    rubberBand->setGeometry(QRect(origin, event->pos()).normalized());
}

void SelectAreaBand::mouseReleaseEvent(QMouseEvent * event)
{
    if(event->button() != Qt::LeftButton)
        return;

    rubberBand->hide();
    this->hide();
    emit areaTaken(QRect(origin, event->pos()).normalized());
}

void SelectAreaBand::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_Escape)
        {
            rubberBand->deleteLater();
            this->deleteLater();
            emit areaCanceled();
        }
}

SelectAreaBand::~SelectAreaBand() {}
