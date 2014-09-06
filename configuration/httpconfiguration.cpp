/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#include "httpconfiguration.h"



HTTPConfiguration::HTTPConfiguration(QWidget * parent) :
    QWidget(parent)
{
    this->setWindowIcon(QIcon(":/icon/base.png"));
    this->setUpUI();

    if(settings.value(Reg::HTTPPort).isNull())
        settings.setValue(Reg::HTTPPort,80);
    if(settings.value(Reg::HTTPFileFieldName).isNull())
        settings.setValue(Reg::HTTPFileFieldName, "uplimgFile");

    host->setText(settings.value(Reg::HTTPHost).toString());
    port->setValue(settings.value(Reg::HTTPPort, 80).toInt());
    username->setText(settings.value(Reg::HTTPUsername).toString());
    password->setText(settings.value(Reg::HTTPPassword).toString());
    password->setEchoMode(QLineEdit::EchoMode::Password);
    webPath->setText(settings.value(Reg::HTTPWebPath).toString());

    if(settings.value(Reg::HTTPLinkFrom).toString() == "FROM_FIXED")
        webPathFromFixed->setChecked(true);
    else
        {
            webPath->setDisabled(true);
            webPathFromHTTPResponse->setChecked(true);
        }

    QObject::connect(host, SIGNAL(textChanged(QString)), this, SLOT(hostSettingModified(QString)));
    QObject::connect(port, SIGNAL(valueChanged(int)), this, SLOT(portSettingModified(int)));
    QObject::connect(username, SIGNAL(textChanged(QString)), this, SLOT(usernameSettingModified(QString)));
    QObject::connect(password, SIGNAL(textChanged(QString)), this, SLOT(passwordSettingModified(QString)));
    QObject::connect(privateKey, SIGNAL(clicked()), this, SLOT(privateKeyClicked()));
    QObject::connect(webPathFromHTTPResponse, SIGNAL(toggled(bool)), this, SLOT(webPathFromHTTPResponseSettingModified(bool)));
    QObject::connect(webPathFromFixed, SIGNAL(toggled(bool)), this, SLOT(webPathFromFixedSettingModified(bool)));
    QObject::connect(webPath, SIGNAL(textChanged(QString)), this, SLOT(webPathSettingModified(QString)));

    QObject::connect(host, SIGNAL(returnPressed()), this, SLOT(close()));
    QObject::connect(webPath, SIGNAL(returnPressed()), this, SLOT(close()));

    QObject::connect(validate, SIGNAL(clicked()), this, SLOT(close()));

}


HTTPConfiguration::~HTTPConfiguration()
{
}

void HTTPConfiguration::setUpUI()
{
    mainFormLayout = new QFormLayout;
    mainGroupLayout = new QGroupBox;

    host = new LineEditBlue;
    port = new QSpinBox;
    port->setMaximum(99999);
    port->setMinimum(0);
    username = new LineEditBlue;
    password = new LineEditBlue;
    privateKey = new ButtonOrange(tr("KEY_COPY"));
    privateKeyWarning = new LabelRed(tr("KEY_WARNING"));


    webPathBox = new GroupBoxBlue(tr("FROM_LINK_TO_DISTRIBUTE"));
    webPathLayout = new QVBoxLayout;
    webPathFromHTTPResponse = new RadioButtonGreen(tr("LINK_FROM_HTTP_RESPONSE"));
    webPathFromFixedLayout = new QHBoxLayout;
    webPathFromFixed = new RadioButtonGreen(tr("LINK_FROM_FIXED_WEBPATH"));
    webPath = new LineEditBlue;
    webPathFromFixedLayout->addWidget(webPathFromFixed);
    webPathFromFixedLayout->addWidget(webPath);
    webPathLayout->addWidget(webPathFromHTTPResponse);
    webPathLayout->addLayout(webPathFromFixedLayout);

    webPathBox->setLayout(webPathLayout);

    mainFormLayout->addRow(tr("YOUR_HOST"), host);
    mainFormLayout->addRow(tr("YOUR_PORT"), port);
    mainFormLayout->addRow(tr("YOUR_USERNAME"), username);
    mainFormLayout->addRow(tr("YOUR_PASSWORD"), password);
    mainFormLayout->addRow(tr("YOUR_KEY"), privateKey);
    mainFormLayout->addRow("", privateKeyWarning);

    secondLayout = new QVBoxLayout;
    secondLayout->addLayout(mainFormLayout);
    secondLayout->addWidget(webPathBox);

    mainGroupLayout = new GroupBoxBlue(tr("SET_HTTP_CREDENTIALS"));
    mainGroupLayout->setLayout(secondLayout);

    validateLayout = new QHBoxLayout;
    validate = new ButtonBlue(tr("Ok"));
    validateLayout->addStretch();
    validateLayout->addWidget(validate);

    layout = new QVBoxLayout;
    layout->addWidget(mainGroupLayout);
    layout->addLayout(validateLayout);
    this->setLayout(layout);
}

void HTTPConfiguration::hostSettingModified(QString text)
{
    if (text[0] != 'h' || text[1] != 't' || text[2] != 't' || text[3] != 'p'
            || text[4] != ':' || text[5] != '/' || text[6] != '/')
        {
            text = "http://" + text;
        }

    settings.setValue(Reg::HTTPHost, text);
}

void HTTPConfiguration::portSettingModified(int value)
{
    settings.setValue(Reg::HTTPPort, value);
}

void HTTPConfiguration::usernameSettingModified(QString content)
{
    settings.setValue(Reg::HTTPUsername, content);
    refillPrivateKey();
}

void HTTPConfiguration::passwordSettingModified(QString content)
{
    settings.setValue(Reg::HTTPPassword, content);
    refillPrivateKey();
}

void HTTPConfiguration::privateKeyClicked()
{
    QApplication::clipboard()->setText(settings.value(Reg::HTTPPrivateKey).toString());
}

void HTTPConfiguration::refillPrivateKey()
{
    QString unhashedKey = username->text() + "|oOo|" + password->text();
    QString hashedKey = QCryptographicHash::hash(unhashedKey.toUtf8(), QCryptographicHash::Sha1).toHex();
    settings.setValue(Reg::HTTPPrivateKey, hashedKey);
}

void HTTPConfiguration::fileFieldNameSettingModified(QString content)
{
    settings.setValue(Reg::HTTPFileFieldName, content);
}

void HTTPConfiguration::webPathSettingModified(QString text)
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

    settings.setValue(Reg::HTTPWebPath, text);

}

void HTTPConfiguration::webPathFromFixedSettingModified(bool checked)
{
    if(checked)
        {
            settings.setValue(Reg::HTTPLinkFrom, "FROM_FIXED");
            webPath->setEnabled(checked);
        }
}

void HTTPConfiguration::webPathFromHTTPResponseSettingModified(bool checked)
{
    if(checked)
        {
            settings.setValue(Reg::HTTPLinkFrom, "FROM_HTTP");
            webPath->setDisabled(checked);
        }
}
