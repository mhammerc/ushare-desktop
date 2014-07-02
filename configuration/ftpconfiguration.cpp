#include "ftpconfiguration.h"


FTPConfiguration::FTPConfiguration(QWidget *parent) :
    QWidget(parent),
    hostSettingName("configuration/ftp/host"),
    portSettingName("configuration/ftp/port"),
    usernameSettingName("configuration/ftp/username"),
    passwordSettingName("configuration/ftp/password"),
    basePathSettingName("configuration/ftp/basePath"),
    webPathSettingName("configuration/ftp/webPath")
{

    this->setUpUI();

    if(settings.value(portSettingName).isNull())
        settings.setValue(portSettingName,21);

    host->setText(settings.value(hostSettingName).toString());
    port->setValue(settings.value(portSettingName, 21).toInt());
    username->setText(settings.value(usernameSettingName).toString());
    password->setText(settings.value(passwordSettingName).toString());
    basePath->setText(settings.value(basePathSettingName).toString());
    webPath->setText(settings.value(webPathSettingName).toString());

    QObject::connect(host, SIGNAL(textChanged(QString)), this, SLOT(hostSettingModified(QString)));
    QObject::connect(port, SIGNAL(valueChanged(int)), this, SLOT(portSettingModified(int)));
    QObject::connect(username, SIGNAL(textChanged(QString)), this, SLOT(usernameSettingModified(QString)));
    QObject::connect(password, SIGNAL(textChanged(QString)), this, SLOT(passwordSettingModified(QString)));
    QObject::connect(basePath, SIGNAL(textChanged(QString)), this, SLOT(basePathSettingModified(QString)));
    QObject::connect(webPath, SIGNAL(textChanged(QString)), this, SLOT(webPathSettingModified(QString)));

    QObject::connect(validate, SIGNAL(clicked()), this, SLOT(close()));
}

void FTPConfiguration::setUpUI()
{
    formLayout = new QFormLayout;

    host = new QLineEdit();
    port = new QSpinBox();
    username = new QLineEdit();
    password = new QLineEdit();
    password->setEchoMode(QLineEdit::Password);
    basePath = new QLineEdit();
    webPath = new QLineEdit();

    formLayout->addRow(tr("Your host :"), host);
    formLayout->addRow(tr("Port of your server :"), port);
    formLayout->addRow(tr("Username to connect :"), username);
    formLayout->addRow(tr("Password to connect :"), password);
    formLayout->addRow(tr("Path to upload directory on distant server :"), basePath);
    formLayout->addRow(tr("URL to web access :"), webPath);

    mainGroupLayout = new QGroupBox(tr("Modify FTP credentials"));
    mainGroupLayout->setLayout(formLayout);

    validateLayout = new QHBoxLayout;
    validate = new QPushButton(tr("Ok"));
    validateLayout->addStretch();
    validateLayout->addWidget(validate);

    layout = new QVBoxLayout;
    layout->addWidget(mainGroupLayout);
    layout->addLayout(validateLayout);
    this->setLayout(layout);
}

void FTPConfiguration::webPathSettingModified(QString text)
{
    if (text[0] != 'h' || text[1] != 't' || text[2] != 't' || text[3] != 'p'
            || text[4] != ':' || text[5] != '/' || text[6] != '/')
        {
            text = "http://" + text;
        }

    if (!text.toStdString().empty() && *text.toStdString().rbegin() != '/')
        text.push_back('/');
    else if (text.toStdString().empty())
        text = "/";

    settings.setValue(webPathSettingName, text);
}

void FTPConfiguration::hostSettingModified(QString text)
{
    settings.setValue(hostSettingName, text);
}

void FTPConfiguration::portSettingModified(int value)
{
    settings.setValue(portSettingName, value);
}

void FTPConfiguration::usernameSettingModified(QString text)
{
    settings.setValue(usernameSettingName, text);
}

void FTPConfiguration::passwordSettingModified(QString text)
{
    settings.setValue(passwordSettingName, text);
}

void FTPConfiguration::basePathSettingModified(QString text)
{
    if (!text.toStdString().empty() && *text.toStdString().rbegin() != '/')
        text.push_back('/');
    else if (text.toStdString().empty())
        text = "/";

    settings.setValue(basePathSettingName, text);
}
