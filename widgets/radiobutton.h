#ifndef RADIOBUTTON_H
#define RADIOBUTTON_H

#include <QRadioButton>

class RadioButtonGreen : public QRadioButton
{
public:
    RadioButtonGreen(QWidget * parent = 0) : QRadioButton(parent)
    {
        setObjectName("green");
    }

    RadioButtonGreen(const QString & text, QWidget * parent = 0) : QRadioButton(text, parent)
    {
        setObjectName("green");
    }
};

#endif // RADIOBUTTON_H
