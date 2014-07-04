#include "HTTPConfiguration.h"



HTTPConfiguration::HTTPConfiguration(QWidget * parent) :
    QWidget(parent),
    hostSettingName("configuration/http/host"),
    portSettingName("configuration/http/port"),
    fileFieldNameSettingName("configuration/http/fieldName"),
    webPathSettingName("configuration/http/webPath")
{
    this->setWindowIcon(QIcon(":/small.png"));
    this->setUpUI();

    if(settings.value(portSettingName).isNull())
        settings.setValue(portSettingName,80);
    if(settings.value(fileFieldNameSettingName).isNull())
        settings.setValue(fileFieldNameSettingName, "uplimgFile");

    host->setText(settings.value(hostSettingName).toString());
    port->setValue(settings.value(portSettingName, 80).toInt());
    fileFieldName->setText(settings.value(fileFieldNameSettingName, "uplimgFile").toString());
    webPath->setText(settings.value(webPathSettingName).toString());

    QObject::connect(host, SIGNAL(textChanged(QString)), this, SLOT(hostSettingModified(QString)));
    QObject::connect(port, SIGNAL(valueChanged(int)), this, SLOT(portSettingModified(int)));
    QObject::connect(fileFieldName, SIGNAL(textChanged(QString)), this, SLOT(fileFieldNameSettingModified(QString)));
    QObject::connect(webPath, SIGNAL(textChanged(QString)), this, SLOT(webPathSettingModified(QString)));

    QObject::connect(validate, SIGNAL(clicked()), this, SLOT(close()));

}


HTTPConfiguration::~HTTPConfiguration()
{
}

void HTTPConfiguration::setUpUI()
{
    formLayout = new QFormLayout;

    host = new QLineEdit();
    port = new QSpinBox();
    fileFieldName = new QLineEdit();
    webPath = new QLineEdit();

    formLayout->addRow(tr("YOUR_HOST"), host);
    formLayout->addRow(tr("YOUR_PORT"), port);
    formLayout->addRow(tr("YOUR_FILE_FIED_NAME"), fileFieldName);
    formLayout->addRow(tr("YOUR_WEB_PATH"), webPath);

    mainGroupLayout = new QGroupBox(tr("SET_HTTP_CREDENTIALS"));
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
