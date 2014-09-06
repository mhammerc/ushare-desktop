/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <QRadioButton>

class RadioButtonGreen : public QRadioButton
{
public:
    RadioButtonGreen(QWidget * parent = 0) : QRadioButton(parent)
    {
        setObjectName("green");
    }

    RadioButtonGreen(const QString & text, QWidget * parent = 0) : QRadioButton(text, parent)
    {
        setObjectName("green");
    }
};

#endif // RADIOBUTTON_H
