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
    QLineEdit * fileFieldName;
    QGroupBox * webPathBox;
    QVBoxLayout * webPathLayout;
    QRadioButton * webPathFromHTTPResponse;
    QHBoxLayout * webPathFromFixedLayout;
    QRadioButton * webPathFromFixed;
    QLineEdit * webPath;

    QHBoxLayout * validateLayout;
    QPushButton * validate;

    void setUpUI();

public slots :
    void hostSettingModified(QString);
    void portSettingModified(int);
    void fileFieldNameSettingModified(QString);
    void webPathSettingModified(QString);
    void webPathFromHTTPResponseSettingModified(bool);
    void webPathFromFixedSettingModified(bool);

};

