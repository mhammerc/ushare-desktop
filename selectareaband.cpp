/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#include "selectareaband.h"
#include "screenmanager.h"


SelectAreaBand::SelectAreaBand(FileManager *manager, QWidget * parent) :
    QLabel(parent)
{
    this->grabKeyboard();
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
    //setPalette(palette);
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

SelectAreaBand::~SelectAreaBand() {releaseKeyboard();}
