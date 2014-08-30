/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#ifndef TABBAR_H
#define TABBAR_H

#include <QTabWidget>
#include <QTabBar>

class TabWidgetBlue : public QTabWidget
{
public:
    TabWidgetBlue(QWidget * parent = 0) : QTabWidget(parent)
    {
        setObjectName("blue");
    }
};

class TabBarBlue : public QTabBar
{
public:
    TabBarBlue(QWidget * parent = 0) : QTabBar(parent)
    {
        setObjectName("blue");
    }
};

#endif // TABBAR_H
