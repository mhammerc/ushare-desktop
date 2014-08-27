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

class ButtonOrange : public QPushButton
{
public:
    ButtonOrange(QWidget * parent = 0) : QPushButton(parent)
    {
        setObjectName("orange");
    }
    ButtonOrange(const QString & text, QWidget * parent = 0): QPushButton(text, parent)
    {
        setObjectName("orange");
    }
    ButtonOrange(const QIcon & icon, const QString & text, QWidget * parent = 0) : QPushButton(icon, text, parent)
    {
        setObjectName("orange");
    }
};

class MinimizeButton : public QPushButton
{
public:
    MinimizeButton(QWidget * parent = 0) : QPushButton(parent)
    {
        setObjectName("MinimizeButton");
    }
    MinimizeButton(const QString & text, QWidget * parent = 0): QPushButton(text, parent)
    {
        setObjectName("MinimizeButton");
    }
    MinimizeButton(const QIcon & icon, const QString & text, QWidget * parent = 0) : QPushButton(icon, text, parent)
    {
        setObjectName("MinimizeButton");
    }
};

class CloseButton : public QPushButton
{
public:
    CloseButton(QWidget * parent = 0) : QPushButton(parent)
    {
        setObjectName("CloseButton");
    }
    CloseButton(const QString & text, QWidget * parent = 0): QPushButton(text, parent)
    {
        setObjectName("CloseButton");
    }
    CloseButton(const QIcon & icon, const QString & text, QWidget * parent = 0) : QPushButton(icon, text, parent)
    {
        setObjectName("CloseButton");
    }
};

#endif // BUTTON_H
