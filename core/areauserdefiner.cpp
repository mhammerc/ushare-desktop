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
    if(e->button() != Qt::LeftButton) return;

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
    if(e->button() != Qt::LeftButton) return;

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
    setGeometry(screen->virtualGeometry().x(), screen->virtualGeometry().y(), screen->virtualGeometry().width(), screen->virtualGeometry().height());
}

