/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#ifndef GROUPBOX_H
#define GROUPBOX_H

#include <QGroupBox>

class GroupBoxBlue : public QGroupBox
{
public:
    GroupBoxBlue(QWidget * parent = 0) : QGroupBox(parent)
    {
        setObjectName("blue");
    }
    GroupBoxBlue(const QString & title, QWidget * parent = 0) : QGroupBox(title, parent)
    {
        setObjectName("blue");
    }
};

#endif // GROUPBOX_H
