/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

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
