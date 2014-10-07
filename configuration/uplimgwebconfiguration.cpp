#include "uplimgwebconfiguration.h"

UplimgWebConfiguration::UplimgWebConfiguration(QWidget *parent) :
    QWidget(parent)
{
    setUpUI();
    fillRow();

    QObject::connect(anonymousAuthMethod, SIGNAL(clicked()), this, SLOT(makeAnonymous()));
    QObject::connect(loginAuthMethod, SIGNAL(clicked()), this, SLOT(makeWithLogin()));
    QObject::connect(username, SIGNAL(textChanged(QString)), this, SLOT(usernameChanged(QString)));
    QObject::connect(password, SIGNAL(textChanged(QString)), this, SLOT(passwordChanged(QString)));
    QObject::connect(validate, SIGNAL(clicked()), this, SLOT(hide()));
}

void UplimgWebConfiguration::setUpUI()
{
    layout = new QVBoxLayout;
    mainFormLayout = new QFormLayout;
    mainGroupLayout = new GroupBoxBlue(tr("CONFIGURE_UPLIMG_WEB"));

    anonymousAuthMethod = new RadioButtonGreen;
    loginAuthMethod = new RadioButtonGreen;
    username = new LineEditBlue;
    password = new LineEditBlue;
    password->setEchoMode(QLineEdit::Password);
    mainFormLayout->addRow(tr("ANONYMOUS"), anonymousAuthMethod);
    mainFormLayout->addRow(tr("LOGIN"), loginAuthMethod);
    mainFormLayout->addRow(tr("USERNAME"), username);
    mainFormLayout->addRow(tr("PASSWORD"), password);

    secondLayout = new QVBoxLayout;
    secondLayout->addLayout(mainFormLayout);

    mainGroupLayout->setLayout(secondLayout);

    validateLayout = new QHBoxLayout;
    validate = new ButtonBlue(tr("Ok"));
    validateLayout->addStretch();
    validateLayout->addWidget(validate);

    layout->addWidget(mainGroupLayout);
    layout->addLayout(validateLayout);
    this->setLayout(layout);
}

void UplimgWebConfiguration::fillRow()
{
    username->setText(settings.value(Reg::UplimgWebUsername).toString());
    password->setText(settings.value(Reg::UplimgWebPassword).toString());
    if(settings.value(Reg::hasUplimgWebLogin).toBool() == true)
    {
        loginAuthMethod->setChecked(true);
    }
    else
    {
        anonymousAuthMethod->setChecked(true);
        username->setDisabled(true);
        password->setDisabled(true);
    }

}

void UplimgWebConfiguration::makeAnonymous()
{
    username->setDisabled(true);
    password->setDisabled(true);

    settings.setValue(Reg::hasUplimgWebLogin, false);
}

void UplimgWebConfiguration::makeWithLogin()
{
   username->setEnabled(true);
   password->setEnabled(true);

   settings.setValue(Reg::hasUplimgWebLogin, true);
}

void UplimgWebConfiguration::usernameChanged(QString username)
{
    settings.setValue(Reg::UplimgWebUsername, username);
}

void UplimgWebConfiguration::passwordChanged(QString pass)
{
    settings.setValue(Reg::UplimgWebPassword, pass);
}
