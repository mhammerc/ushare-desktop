#ifndef GROUPBOX_H
#define GROUPBOX_H

#include <QGroupBox>

class GroupBoxBlue : public QGroupBox
{
public:
    GroupBoxBlue(QWidget * parent = 0) : QGroupBox(parent)
    {
        setObjectName("blue");
    }
    GroupBoxBlue(const QString & title, QWidget * parent = 0) : QGroupBox(title, parent)
    {
        setObjectName("blue");
    }
};

#endif // GROUPBOX_H
