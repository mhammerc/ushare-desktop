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
