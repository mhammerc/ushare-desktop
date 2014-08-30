/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#pragma once

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

class HTTPConfiguration : public QWidget
{
    Q_OBJECT
public:
    explicit HTTPConfiguration(QWidget * parent = 0);
    ~HTTPConfiguration();

protected:
    QSettings settings;

    //Main layout and main form
    QVBoxLayout * layout;
    QGroupBox * mainGroupLayout;
    QFormLayout * mainFormLayout;
    QVBoxLayout * secondLayout;

    QLineEdit * host;
    QSpinBox * port;
    QLineEdit * username;
    QLineEdit * password;
    QPushButton * privateKey;
    QLabel * privateKeyWarning;
    QGroupBox * webPathBox;
    QVBoxLayout * webPathLayout;
    QRadioButton * webPathFromHTTPResponse;
    QHBoxLayout * webPathFromFixedLayout;
    QRadioButton * webPathFromFixed;
    QLineEdit * webPath;

    QHBoxLayout * validateLayout;
    ButtonBlue * validate;

    void setUpUI();

public slots :
    void hostSettingModified(QString);
    void portSettingModified(int);
    void usernameSettingModified(QString);
    void passwordSettingModified(QString);
    void privateKeyClicked();
    void refillPrivateKey();
    void fileFieldNameSettingModified(QString);
    void webPathSettingModified(QString);
    void webPathFromHTTPResponseSettingModified(bool);
    void webPathFromFixedSettingModified(bool);

};

