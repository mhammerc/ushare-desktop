#ifndef CHECKBOX_H
#define CHECKBOX_H

#include <QCheckBox>

class CheckBoxGreen : public QCheckBox
{
public:

    CheckBoxGreen(QWidget *parent = 0) : QCheckBox(parent)
    {
        setObjectName("green");
    }
    CheckBoxGreen(const QString &text, QWidget* parent=0): QCheckBox(text,parent)
    {
        setObjectName("green");
    }
};

#endif // CHECKBOX_H
