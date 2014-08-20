#ifndef SLIDER_H
#define SLIDER_H

#include <QSlider>

class SliderGreen : public QSlider
{
public:
    SliderGreen(QWidget * parent = 0) : QSlider(parent)
    {
        setObjectName("green");
    }
    SliderGreen(Qt::Orientation orientation, QWidget * parent = 0) : QSlider(orientation, parent)
    {
        setObjectName("green");
    }
};

class SliderOrange : public QSlider
{
public:
    SliderOrange(QWidget * parent = 0) : QSlider(parent)
    {
        setObjectName("orange");
    }
    SliderOrange(Qt::Orientation orientation, QWidget * parent = 0) : QSlider(orientation, parent)
    {
        setObjectName("orange");
    }
};

class SliderBlue : public QSlider
{
public:
    SliderBlue(QWidget * parent = 0) : QSlider(parent)
    {
        setObjectName("blue");
    }
    SliderBlue(Qt::Orientation orientation, QWidget * parent = 0) : QSlider(orientation, parent)
    {
        setObjectName("blue");
    }
};

#endif // SLIDER_H
