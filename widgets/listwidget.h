#ifndef LISTWIDGET_H
#define LISTWIDGET_H

#include <QListWidget>

class ListWidgetGreen : public QListWidget
{
public:
    ListWidgetGreen(QWidget * parent = 0) : QListWidget(parent)
    {
        setObjectName("green");
    }
};

class ListWidgetOrange : public QListWidget
{
public:
    ListWidgetOrange(QWidget * parent = 0) : QListWidget(parent)
    {
        setObjectName("orange");
    }
};

class ListWidgetBlue : public QListWidget
{
public:
    ListWidgetBlue(QWidget * parent = 0) : QListWidget(parent)
    {
        setObjectName("blue");
    }
};

#endif // LISTWIDGET_H
