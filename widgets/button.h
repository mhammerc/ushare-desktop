#ifndef BUTTON_H
#define BUTTON_H

#include <QPushButton>

class ButtonBlue : public QPushButton
{
public:
    ButtonBlue(QWidget * parent = 0) : QPushButton(parent)
    {
        setObjectName("blue");
    }
    ButtonBlue(const QString & text, QWidget * parent = 0): QPushButton(text, parent)
    {
        setObjectName("blue");
    }
    ButtonBlue(const QIcon & icon, const QString & text, QWidget * parent = 0) : QPushButton(icon, text, parent)
    {
        setObjectName("blue");
    }
};

class MinimizeButton : public QPushButton
{
public:
    MinimizeButton(QWidget * parent = 0) : QPushButton(parent)
    {
        setObjectName("BlackMinimizeButton16");
    }
    MinimizeButton(const QString & text, QWidget * parent = 0): QPushButton(text, parent)
    {
        setObjectName("BlackMinimizeButton16");
    }
    MinimizeButton(const QIcon & icon, const QString & text, QWidget * parent = 0) : QPushButton(icon, text, parent)
    {
        setObjectName("BlackMinimizeButton16");
    }
};

class CloseButton : public QPushButton
{
public:
    CloseButton(QWidget * parent = 0) : QPushButton(parent)
    {
        setObjectName("BlackCloseButton16");
    }
    CloseButton(const QString & text, QWidget * parent = 0): QPushButton(text, parent)
    {
        setObjectName("BlackCloseButton16");
    }
    CloseButton(const QIcon & icon, const QString & text, QWidget * parent = 0) : QPushButton(icon, text, parent)
    {
        setObjectName("BlackCloseButton16");
    }
};

#endif // BUTTON_H
