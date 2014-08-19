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
        setObjectName("UplimgText16");
    }
    UplimgTitle(const QString & text, QWidget * parent = 0, Qt::WindowFlags f = 0): QLabel(text, parent, f)
    {
        setObjectName("UplimgText16");
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
