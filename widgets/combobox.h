/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>

class ComboBoxGreen : public QComboBox
{
public:
    ComboBoxGreen(QWidget * parent = 0) : QComboBox(parent)
    {
        setObjectName("green");
    }
};

class ComboBoxOrange : public QComboBox
{
public:
    ComboBoxOrange(QWidget * parent = 0) : QComboBox(parent)
    {
        setObjectName("orange");
    }
};

class ComboBoxBlue : public QComboBox
{
public:
    ComboBoxBlue(QWidget * parent = 0) : QComboBox(parent)
    {
        setObjectName("blue");
    }
};

#endif // COMBOBOX_H
