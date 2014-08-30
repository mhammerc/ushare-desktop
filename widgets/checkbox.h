/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QCheckBox>

class CheckBoxGreen : public QCheckBox
{
public:

    CheckBoxGreen(QWidget *parent = 0) : QCheckBox(parent)
    {
        setObjectName("green");
    }
    CheckBoxGreen(const QString &text, QWidget* parent=0): QCheckBox(text,parent)
    {
        setObjectName("green");
    }
};

#endif // CHECKBOX_H
