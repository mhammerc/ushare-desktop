#ifndef COMBOBOX_H
#define COMBOBOX_H

#include <QComboBox>

class ComboBoxGreen : public QComboBox
{
public:
    ComboBoxGreen(QWidget * parent = 0) : QComboBox(parent)
    {
        setObjectName("green");
    }
};

class ComboBoxOrange : public QComboBox
{
public:
    ComboBoxOrange(QWidget * parent = 0) : QComboBox(parent)
    {
        setObjectName("orange");
    }
};

class ComboBoxBlue : public QComboBox
{
public:
    ComboBoxBlue(QWidget * parent = 0) : QComboBox(parent)
    {
        setObjectName("blue");
    }
};

#endif // COMBOBOX_H
