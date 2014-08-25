#ifndef LINEEDIT_H
#define LINEEDIT_H

#include <QLineEdit>

class LineEditBlue : public QLineEdit
{
public:
    LineEditBlue(QWidget * parent = 0) : QLineEdit(parent)
    {
        setObjectName("blue");
    }

    LineEditBlue(QString const &contents, QWidget * parent = 0) : QLineEdit(contents, parent)
    {
        setObjectName("blue");
    }
};

class LineEditGreen : public QLineEdit
{
public:
    LineEditGreen(QWidget * parent = 0) : QLineEdit(parent)
    {
        setObjectName("green");
    }

    LineEditGreen(QString const &contents, QWidget * parent = 0) : QLineEdit(contents, parent)
    {
        setObjectName("green");
    }
};

class LineEditOrange : public QLineEdit
{
public:
    LineEditOrange(QWidget * parent = 0) : QLineEdit(parent)
    {
        setObjectName("orange");
    }

    LineEditOrange(QString const &contents, QWidget * parent = 0) : QLineEdit(contents, parent)
    {
        setObjectName("orange");
    }
};

class LineEditRed : public QLineEdit
{
public:
    LineEditRed(QWidget * parent = 0) : QLineEdit(parent)
    {
        setObjectName("red");
    }

    LineEditRed(QString const &contents, QWidget * parent = 0) : QLineEdit(contents, parent)
    {
        setObjectName("red");
    }
};

#endif // LINEEDIT_H
