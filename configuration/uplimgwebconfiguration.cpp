#include "uplimgwebconfiguration.h"

UplimgWebConfiguration::UplimgWebConfiguration(QWidget *parent) :
    QWidget(parent)
{
    setUpUI();
}

void UplimgWebConfiguration::setUpUI()
{
    layout = new QVBoxLayout;
    mainFormLayout = new QFormLayout;
    mainGroupLayout = new GroupBoxBlue(tr("CONFIGURE_UPLIMG_WEB"));

    whatIAm = new QLabel(tr("PRESENT_UPLIMG_WEB"));

    anonymousAuthMethod = new RadioButtonGreen;
    loginAuthMethod = new RadioButtonGreen;
    username = new LineEditBlue;
    password = new LineEditBlue;
    mainFormLayout->addRow(tr("ANONYMOUS"), anonymousAuthMethod);
    mainFormLayout->addRow(tr("LOGIN"), loginAuthMethod);
    mainFormLayout->addRow(tr("USERNAME"), username);
    mainFormLayout->addRow(tr("PASSWORD"), password);

    secondLayout = new QVBoxLayout;
    secondLayout->addWidget(whatIAm);
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
