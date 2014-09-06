/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#ifndef LABEL_H
#define LABEL_H

#include <QLabel>

class LabelBlue : public QLabel
{
public:
    LabelBlue(QWidget * parent = 0, Qt::WindowFlags f = 0) : QLabel(parent,f)
    {
        setObjectName("blue");
    }
    LabelBlue(const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0): QLabel(text, parent, f)
    {
        setObjectName("blue");
    }
};

class LabelGreen : public QLabel
{
public:
    LabelGreen(QWidget * parent = 0, Qt::WindowFlags f = 0) : QLabel(parent,f)
    {
        setObjectName("green");
    }
    LabelGreen(const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0): QLabel(text, parent, f)
    {
        setObjectName("green");
    }
};

class LabelOrange : public QLabel
{
public:
    LabelOrange(QWidget * parent = 0, Qt::WindowFlags f = 0) : QLabel(parent,f)
    {
        setObjectName("orange");
    }
    LabelOrange(const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0): QLabel(text, parent, f)
    {
        setObjectName("orange");
    }
};

class LabelRed : public QLabel
{
public:
    LabelRed(QWidget * parent = 0, Qt::WindowFlags f = 0) : QLabel(parent,f)
    {
        setObjectName("red");
    }
    LabelRed(const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0): QLabel(text, parent, f)
    {
        setObjectName("red");
    }
};

class LabelGray : public QLabel
{
public:
    LabelGray(QWidget * parent = 0, Qt::WindowFlags f = 0) : QLabel(parent,f)
    {
        setObjectName("gray");
    }
    LabelGray(const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0): QLabel(text, parent, f)
    {
        setObjectName("gray");
    }
};

class UplimgIcon : public QLabel
{
public:
    UplimgIcon(QWidget * parent = 0, Qt::WindowFlags f = 0) : QLabel(parent,f)
    {
        setObjectName("UplimgIconBlue16");
    }
    UplimgIcon(const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0): QLabel(text, parent, f)
    {
        setObjectName("UplimgIconBlue16");
    }
};

class UplimgTitle : public QLabel
{
public:
    UplimgTitle(QWidget * parent = 0, Qt::WindowFlags f = 0) : QLabel(parent,f)
    {
        setObjectName("UplimgText");
    }
    UplimgTitle(const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0): QLabel(text, parent, f)
    {
        setObjectName("UplimgText");
    }
};

class LabelWithoutBackground : public QLabel
{
public:
    LabelWithoutBackground(QWidget * parent = 0, Qt::WindowFlags f = 0) : QLabel(parent,f)
    {
        setObjectName("noBackground");
    }
    LabelWithoutBackground(const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0): QLabel(text, parent, f)
    {
        setObjectName("noBackground");
    }
};

#endif // LABEL_H
