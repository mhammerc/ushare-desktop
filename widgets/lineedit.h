/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

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
