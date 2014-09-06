/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#include "ftpconfiguration.h"


FTPConfiguration::FTPConfiguration(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowIcon(QIcon(":/icon/base.png"));
    this->setUpUI();

    if(settings.value(Reg::FTPPort).isNull())
        settings.setValue(Reg::FTPPort,21);

    host->setText(settings.value(Reg::FTPHost).toString());
    port->setValue(settings.value(Reg::FTPPort, 21).toInt());
    username->setText(settings.value(Reg::FTPUsername).toString());
    password->setText(settings.value(Reg::FTPPassword).toString());
    basePath->setText(settings.value(Reg::FTPBasePath).toString());
    webPath->setText(settings.value(Reg::FTPWebPath).toString());

    QObject::connect(host, SIGNAL(textChanged(QString)), this, SLOT(hostSettingModified(QString)));
    QObject::connect(port, SIGNAL(valueChanged(int)), this, SLOT(portSettingModified(int)));
    QObject::connect(username, SIGNAL(textChanged(QString)), this, SLOT(usernameSettingModified(QString)));
    QObject::connect(password, SIGNAL(textChanged(QString)), this, SLOT(passwordSettingModified(QString)));
    QObject::connect(basePath, SIGNAL(textChanged(QString)), this, SLOT(basePathSettingModified(QString)));
    QObject::connect(webPath, SIGNAL(textChanged(QString)), this, SLOT(webPathSettingModified(QString)));

    QObject::connect(host, SIGNAL(returnPressed()), this, SLOT(close()));
    QObject::connect(username, SIGNAL(returnPressed()), this, SLOT(close()));
    QObject::connect(password, SIGNAL(returnPressed()), this, SLOT(close()));
    QObject::connect(basePath, SIGNAL(returnPressed()), this, SLOT(close()));
    QObject::connect(webPath, SIGNAL(returnPressed()), this, SLOT(close()));

    QObject::connect(validate, SIGNAL(clicked()), this, SLOT(close()));
}

void FTPConfiguration::setUpUI()
{
    formLayout = new QFormLayout;

    host = new LineEditBlue();
    port = new QSpinBox();
    username = new LineEditBlue();
    password = new LineEditBlue();
    password->setEchoMode(QLineEdit::EchoMode::Password);
    basePath = new LineEditBlue();
    webPath = new LineEditBlue();

    formLayout->addRow(tr("SET_HOST"), host);
    formLayout->addRow(tr("SET_PORT"), port);
    formLayout->addRow(tr("SET_USERNAME"), username);
    formLayout->addRow(tr("SET_PASSWORD"), password);
    formLayout->addRow(tr("PATh_ON_DISTANT_SERVER"), basePath);
    formLayout->addRow(tr("ONLINE_URL"), webPath);

    mainGroupLayout = new GroupBoxBlue(tr("SET_FTP_CREDENTIALS"));
    mainGroupLayout->setLayout(formLayout);

    validateLayout = new QHBoxLayout;
    validate = new ButtonBlue(tr("Ok"));
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

    settings.setValue(Reg::FTPWebPath, text);
}

void FTPConfiguration::hostSettingModified(QString text)
{
    settings.setValue(Reg::FTPHost, text);
}

void FTPConfiguration::portSettingModified(int value)
{
    settings.setValue(Reg::FTPPort, value);
}

void FTPConfiguration::usernameSettingModified(QString text)
{
    settings.setValue(Reg::FTPUsername, text);
}

void FTPConfiguration::passwordSettingModified(QString text)
{
    settings.setValue(Reg::FTPPassword, text);
}

void FTPConfiguration::basePathSettingModified(QString text)
{
    if (!text.toStdString().empty() && *text.toStdString().rbegin() != '/')
        text.push_back('/');
    else if (text.toStdString().empty())
        text = "/";

    settings.setValue(Reg::FTPBasePath, text);
}
