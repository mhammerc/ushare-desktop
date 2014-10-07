/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

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

class ButtonTwitter : public QPushButton
{
public:
    ButtonTwitter(QWidget * parent = 0) : QPushButton(parent)
    {
        setObjectName("twitter");
    }
    ButtonTwitter(const QString & text, QWidget * parent = 0): QPushButton(text, parent)
    {
        setObjectName("twitter");
    }
    ButtonTwitter(const QIcon & icon, const QString & text, QWidget * parent = 0) : QPushButton(icon, text, parent)
    {
        setObjectName("twitter");
    }
};

#endif // BUTTON_H
