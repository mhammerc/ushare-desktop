#include "httpconfiguration.h"



HTTPConfiguration::HTTPConfiguration(QWidget * parent) :
    QWidget(parent),
    hostSettingName("configuration/http/host"),
    portSettingName("configuration/http/port"),
    fileFieldNameSettingName("configuration/http/fieldName"),
    webPathSettingName("configuration/http/webPath"),
    linkFromSettingName("configuration/http/linkFrom")
{
    this->setWindowIcon(QIcon(":/icon/base.png"));
    this->setUpUI();

    if(settings.value(portSettingName).isNull())
        settings.setValue(portSettingName,80);
    if(settings.value(fileFieldNameSettingName).isNull())
        settings.setValue(fileFieldNameSettingName, "uplimgFile");

    host->setText(settings.value(hostSettingName).toString());
    port->setValue(settings.value(portSettingName, 80).toInt());
    fileFieldName->setText(settings.value(fileFieldNameSettingName, "uplimgFile").toString());
    webPath->setText(settings.value(webPathSettingName).toString());

    if(settings.value(linkFromSettingName).toString() == "FROM_FIXED")
        webPathFromFixed->setChecked(true);
    else
    {
        webPath->setDisabled(true);
        webPathFromHTTPResponse->setChecked(true);
    }

    QObject::connect(host, SIGNAL(textChanged(QString)), this, SLOT(hostSettingModified(QString)));
    QObject::connect(port, SIGNAL(valueChanged(int)), this, SLOT(portSettingModified(int)));
    QObject::connect(fileFieldName, SIGNAL(textChanged(QString)), this, SLOT(fileFieldNameSettingModified(QString)));
    QObject::connect(webPathFromHTTPResponse, SIGNAL(toggled(bool)), this, SLOT(webPathFromHTTPResponseSettingModified(bool)));
    QObject::connect(webPathFromFixed, SIGNAL(toggled(bool)), this, SLOT(webPathFromFixedSettingModified(bool)));
    QObject::connect(webPath, SIGNAL(textChanged(QString)), this, SLOT(webPathSettingModified(QString)));

    QObject::connect(validate, SIGNAL(clicked()), this, SLOT(close()));

}


HTTPConfiguration::~HTTPConfiguration()
{
}

void HTTPConfiguration::setUpUI()
{
    mainFormLayout = new QFormLayout;
    mainGroupLayout = new QGroupBox;

    host = new QLineEdit;
    port = new QSpinBox;
    fileFieldName = new QLineEdit;

    webPathBox = new QGroupBox(tr("FROM_LINK_TO_DISTRIBUTE"));
    webPathLayout = new QVBoxLayout;
    webPathFromHTTPResponse = new QRadioButton(tr("LINK_FROM_HTTP_RESPONSE"));
    webPathFromFixedLayout = new QHBoxLayout;
    webPathFromFixed = new QRadioButton(tr("LINK_FROM_FIXED_WEBPATH"));
    webPath = new QLineEdit;
    webPathFromFixedLayout->addWidget(webPathFromFixed);
    webPathFromFixedLayout->addWidget(webPath);
    webPathLayout->addWidget(webPathFromHTTPResponse);
    webPathLayout->addLayout(webPathFromFixedLayout);

    webPathBox->setLayout(webPathLayout);

    mainFormLayout->addRow(tr("YOUR_HOST"), host);
    mainFormLayout->addRow(tr("YOUR_PORT"), port);
    mainFormLayout->addRow(tr("YOUR_FILE_FIED_NAME"), fileFieldName);

    secondLayout = new QVBoxLayout;
    secondLayout->addLayout(mainFormLayout);
    secondLayout->addWidget(webPathBox);

    mainGroupLayout = new QGroupBox(tr("SET_HTTP_CREDENTIALS"));
    mainGroupLayout->setLayout(secondLayout);

    validateLayout = new QHBoxLayout;
    validate = new QPushButton(tr("Ok"));
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

    settings.setValue(hostSettingName, text);
}

void HTTPConfiguration::portSettingModified(int value)
{
    settings.setValue(portSettingName, value);
}

void HTTPConfiguration::fileFieldNameSettingModified(QString content)
{
    settings.setValue(fileFieldNameSettingName, content);
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

    settings.setValue(webPathSettingName, text);

}

void HTTPConfiguration::webPathFromFixedSettingModified(bool checked)
{
    if(checked)
        {
            settings.setValue(linkFromSettingName, "FROM_FIXED");
            webPath->setEnabled(checked);
        }
}

void HTTPConfiguration::webPathFromHTTPResponseSettingModified(bool checked)
{
    if(checked)
    {
        settings.setValue(linkFromSettingName, "FROM_HTTP");
        webPath->setDisabled(checked);
    }
}
