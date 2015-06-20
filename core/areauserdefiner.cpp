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

#include "areauserdefiner.h"

AreaUserDefiner::AreaUserDefiner(QColor areaColor)
{
    setCursor(Qt::CrossCursor);
    setWindowFlags(Qt::FramelessWindowHint);

    rubberBand = new QRubberBand(QRubberBand::Rectangle, this);

    QPalette palette;
    palette.setColor(QPalette::Normal, QPalette::Highlight, areaColor);
    rubberBand->setPalette(palette);
}

AreaUserDefiner::~AreaUserDefiner()
{
    releaseKeyboard();
}

void AreaUserDefiner::mousePressEvent(QMouseEvent *e)
{
    if(e->button() != Qt::LeftButton)
        return;

    origin = e->pos();
    rubberBand->setGeometry(QRect(origin, QSize(0,0)));
    rubberBand->show();
}

void AreaUserDefiner::mouseMoveEvent(QMouseEvent *e)
{
    rubberBand->setGeometry(QRect(origin, e->pos()).normalized());
}

void AreaUserDefiner::mouseReleaseEvent(QMouseEvent *e)
{
    if(e->button() != Qt::LeftButton)
        return;

    QRect zone = QRect(origin, e->pos()).normalized();

    if(zone.height() <= 1)
        return;

    hide();
    emit areaTaken(QRect(origin, e->pos()).normalized());
}

void AreaUserDefiner::keyPressEvent(QKeyEvent *e)
{
    if(e->key() == Qt::Key_Escape)
        emit areaCanceled();
}

void AreaUserDefiner::start()
{
    this->grabKeyboard();
    QScreen * screen = QApplication::primaryScreen();
    show();
    setWindowState(Qt::WindowActive);
    setGeometry(screen->virtualGeometry().x(), screen->virtualGeometry().y(), screen->virtualGeometry().width(), screen->virtualGeometry().height());
}

