/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#ifndef UPLIMGWEBCONFIGURATION_H
#define UPLIMGWEBCONFIGURATION_H

#include <QWidget>
#include <QString>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLineEdit>
#include <QLabel>
#include <QSpinBox>
#include <QSettings>
#include <QHBoxLayout>
#include <QPushButton>
#include <QGroupBox>
#include <QRadioButton>
#include <QCryptographicHash>

#include "shared.h"

class UplimgWebConfiguration : public QWidget
{
    Q_OBJECT
public:
    explicit UplimgWebConfiguration(QWidget *parent = 0);

protected:
    QSettings settings;

    //Main layout and main form
    QVBoxLayout * layout;
    QGroupBox * mainGroupLayout;
    QLabel * whatIAm;
    QFormLayout * mainFormLayout;
    QVBoxLayout * secondLayout;

    QLineEdit * username;
    QLineEdit * password;

    QGroupBox * authMethodBox;
    QVBoxLayout * authMethodLayout;
    QRadioButton * anonymousAuthMethod;
    QRadioButton * loginAuthMethod;

    QHBoxLayout * validateLayout;
    ButtonBlue * validate;

    void setUpUI();

signals:

public slots:

};

#endif // UPLIMGWEBCONFIGURATION_H
