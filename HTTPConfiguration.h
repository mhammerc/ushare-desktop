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

class HTTPConfiguration : public QWidget
{
    Q_OBJECT
public:
    explicit HTTPConfiguration(QWidget * parent = 0);
    ~HTTPConfiguration();

protected:
    QSettings settings;

    const QString hostSettingName;
    const QString portSettingName;
    const QString fileFieldNameSettingName;
    const QString webPathSettingName;

    //Main layout and main form
    QVBoxLayout * layout;
    QGroupBox * mainGroupLayout;
    QFormLayout * formLayout;

    QLineEdit * host;
    QSpinBox * port;
    QLineEdit * fileFieldName;
    QLineEdit * webPath;

    QHBoxLayout * validateLayout;
    QPushButton * validate;

    void setUpUI();

public slots :
    void hostSettingModified(QString);
    void portSettingModified(int);
    void fileFieldNameSettingModified(QString);
    void webPathSettingModified(QString);

};

