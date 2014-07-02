#include "configurationwindows.h"


ConfigurationWindows::ConfigurationWindows(QWidget *parent) :
    QWidget(parent), windowTitle(tr("Uplimg configuration")),
    runOnStartupSettingName("configuration/runOnStartup"),
    showNotificationsSettingName("configuration/showNotifications"),
    playSoundSettingName("configuration/playSound"),
    langSettingName("configuration/lang"),
    FTPMethodSettingName("configuration/ftp"),
    choosedMethodSettingName("configuration/method")
{

    this->setWindowTitle(windowTitle);
    this->setFixedSize(530, 290);

    this->setUpUI();

    /* Load Settings */
    runOnStartup->setChecked(settings.value(runOnStartupSettingName, true).toBool());
    showNotifications->setChecked(settings.value(showNotificationsSettingName, true).toBool());
    playSound->setChecked(settings.value(playSoundSettingName, true).toBool());
    lang->setCurrentText(settings.value(langSettingName, "English").toString());

    if (settings.value(choosedMethodSettingName).toString() == "FTP")
        FTPMethod->setChecked(true);
    else if (settings.value(choosedMethodSettingName).toString() == "HTTP")
        HTTPMethod->setChecked(true);

    /* Settings Modifier */
    QObject::connect(runOnStartup, SIGNAL(toggled(bool)), this, SLOT(runOnStartupSettingModified(bool)));
    QObject::connect(showNotifications, SIGNAL(toggled(bool)), this, SLOT(showNotificationSettingModified(bool)));
    QObject::connect(playSound, SIGNAL(toggled(bool)), this, SLOT(playSoundSettingModified(bool)));
    QObject::connect(lang, SIGNAL(currentTextChanged(QString)), this, SLOT(langSettingModified(QString)));

    QObject::connect(FTPMethod, SIGNAL(toggled(bool)), this, SLOT(FTPMethodSettingModified(bool)));
    QObject::connect(HTTPMethod, SIGNAL(toggled(bool)), this, SLOT(HTTPMethodSettingModified(bool)));

    QObject::connect(configureFTPButton, SIGNAL(clicked()), this, SLOT(configureFTP()));
    QObject::connect(configureHTTPButton, SIGNAL(clicked()), this, SLOT(configureHTTP()));

    QObject::connect(validate, SIGNAL(clicked()), this, SLOT(hide()));

    FTPConf = new FTPConfiguration();
    HTTPConf = new HTTPConfiguration();

    this->setLayout(mainLayout);
}

void ConfigurationWindows::setUpUI()
{
    windowContent = new QTabWidget();
    mainLayout = new QVBoxLayout();

    this->setUpGeneralSectionUI();
    this->setUpHotkeysSectionUI();
    this->setUpCreditsSectionUI();

    mainLayout->addWidget(windowContent);
}

void ConfigurationWindows::setUpCreditsSectionUI()
{
    creditSection = new QWidget;
    windowContent->addTab(creditSection, tr("Credits"));
}

void ConfigurationWindows::setUpHotkeysSectionUI()
{
    hotkeysSection = new QWidget;
    windowContent->addTab(hotkeysSection, tr("Hotkeys"));
}

void ConfigurationWindows::setUpGeneralSectionUI()
{
    generalSection = new QWidget;

    formGeneral = new QFormLayout();

    runOnStartup = new QCheckBox();
    formGeneral->addRow(tr("Run on startup"), runOnStartup);

    showNotifications = new QCheckBox();
    formGeneral->addRow(tr("Show notifications when event take place"), showNotifications);

    playSound = new QCheckBox();
    formGeneral->addRow(tr("Play sounds when event take place"), playSound);

    lang = new QComboBox();
    lang->addItem("English");
    lang->addItem("Français");
    formGeneral->addRow(tr("Lang of the application"), lang);

    onlineServicesLayout = new QVBoxLayout;

    FTPLayout = new QHBoxLayout;
    FTPMethod = new QRadioButton(tr("Use FTP to send pictures"));
    configureFTPButton = new QPushButton(tr("Configure FTP..."));
    FTPLayout->addWidget(FTPMethod);
    FTPLayout->addWidget(configureFTPButton);

    HTTPLayout = new QVBoxLayout;
    HTTPLayoutForRadioAndPushButton = new QHBoxLayout;
    HTTPMethod = new QRadioButton(tr("Send HTTP request to put pictures online"));
    configureHTTPButton = new QPushButton(tr("Configure HTTP POST..."));
    HTTPLayoutForRadioAndPushButton->addWidget(HTTPMethod);
    HTTPLayoutForRadioAndPushButton->addWidget(configureHTTPButton);
    HTTPWarning = new QLabel(tr("<font size='2'><span style='color:blue;'>(!)</span> Only for advanced users</font>"));
    HTTPLayout->addLayout(HTTPLayoutForRadioAndPushButton);
    HTTPLayout->addWidget(HTTPWarning);

    onlineServicesLayout->addLayout(FTPLayout);
    onlineServicesLayout->addLayout(HTTPLayout);

    onlineServices = new QGroupBox("Online services");
    onlineServices->setLayout(onlineServicesLayout);

    validate = new QPushButton("Ok");
    validateLayout = new QHBoxLayout;
    validateLayout->addStretch();
    validateLayout->addWidget(validate);


    generalLayout = new QVBoxLayout;
    generalLayout->addLayout(formGeneral);
    generalLayout->addWidget(onlineServices);
    generalLayout->addLayout(validateLayout);
    generalLayout->addStretch();



    generalSection->setLayout(generalLayout);

    windowContent->addTab(generalSection, tr("General", "Configuration menu, general section"));
}

void ConfigurationWindows::configureFTP()
{
    FTPConf->show();
}

void ConfigurationWindows::configureHTTP()
{
    HTTPConf->show();
}

void ConfigurationWindows::FTPMethodSettingModified(bool checked)
{
    if (!checked)
        return;

    settings.setValue(choosedMethodSettingName, "FTP");
}

void ConfigurationWindows::HTTPMethodSettingModified(bool checked)
{
    if (!checked)
        return;

    settings.setValue(choosedMethodSettingName, "HTTP");
}

void ConfigurationWindows::runOnStartupSettingModified(bool checked)
{
    settings.setValue(runOnStartupSettingName, checked);
}

void ConfigurationWindows::showNotificationSettingModified(bool checked)
{
    settings.setValue(showNotificationsSettingName, checked);
}

void ConfigurationWindows::playSoundSettingModified(bool checked)
{
    settings.setValue(playSoundSettingName, checked);
}

void ConfigurationWindows::langSettingModified(QString newValue)
{
    settings.setValue(langSettingName, newValue);

    /*QTranslator translator;
    if (newValue == "Français")
        if (translator.load("C:/uplimg_fr.qm"))
            std::cerr << "ok";
    QApplication::installTranslator(&translator);*/
}

void ConfigurationWindows::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}

