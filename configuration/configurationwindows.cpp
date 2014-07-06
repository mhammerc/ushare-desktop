#include "configurationwindows.h"
#include "systemtrayicon.h"


ConfigurationWindows::ConfigurationWindows(SystemTrayIcon * parent, QWidget *qwidget) :
    QWidget(qwidget), windowTitle(tr("UPLIMG_CONFIGURATION")),
    runOnStartupSettingName("configuration/runOnStartup"),
    showNotificationsSettingName("configuration/showNotifications"),
    playSoundSettingName("configuration/playSound"),
    copyToClipboardSettingName("configuration/clipboard"),
    langSettingName("configuration/lang"),
    FTPMethodSettingName("configuration/ftp"),
    choosedMethodSettingName("configuration/method")
{
    this->parent = parent;
    QObject::connect(this, SIGNAL(easterEgg()), parent, SLOT(enableEasterEgg()));

    this->setWindowIcon(QIcon(":/small.png"));
    this->setWindowTitle(windowTitle);

    this->setUpUI();

    this->setFixedSize(530, 300);

    /* Load Settings */
    runOnStartup->setChecked(settings.value(runOnStartupSettingName, true).toBool());
    showNotifications->setChecked(settings.value(showNotificationsSettingName, true).toBool());
    playSound->setChecked(settings.value(playSoundSettingName, true).toBool());
    copyToClipboard->setChecked(settings.value(copyToClipboardSettingName, true).toBool());
    lang->setCurrentText(settings.value(langSettingName, "English").toString());

    if (settings.value(choosedMethodSettingName).toString() == "FTP")
        FTPMethod->setChecked(true);
    else if (settings.value(choosedMethodSettingName).toString() == "HTTP")
        HTTPMethod->setChecked(true);

    /* Settings Modifier */
    QObject::connect(runOnStartup, SIGNAL(toggled(bool)), this, SLOT(runOnStartupSettingModified(bool)));
    QObject::connect(showNotifications, SIGNAL(toggled(bool)), this, SLOT(showNotificationSettingModified(bool)));
    QObject::connect(playSound, SIGNAL(toggled(bool)), this, SLOT(playSoundSettingModified(bool)));
    QObject::connect(copyToClipboard, SIGNAL(toggled(bool)), this, SLOT(copyToClipboardSettingModified(bool)));
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
    creditLayout = new QVBoxLayout;

    //Header
    openSourceText = new QLabel(tr("SOFTWARE_FREE_OPEN_SOURCE", "This software is open source and entirely free to use."));

    //Made with
    SFMLLicence = new QTextEdit;
    QFile SFMLLicenceFile(":/SFML_LICENCE.txt");
    SFMLLicenceFile.open(QIODevice::ReadOnly);
    SFMLLicence->setText(SFMLLicenceFile.readAll());
    SFMLLicence->setWindowTitle(tr("SFML Licence"));
    SFMLLicence->setReadOnly(true);
    SFMLLicence->setFixedSize(400,280);

    madeWithLayout = new QHBoxLayout;
    madeWithQt = new QPushButton(tr("MADE_WITH_QT", "Made with the flexibility of Qt"));
    madeWithSFML = new QPushButton(tr("MADE_WITH_SFML", "Made with the lightness of SFML"));
    madeWithLayout->addWidget(madeWithQt);
    madeWithLayout->addStretch();
    madeWithLayout->addWidget(madeWithSFML);
    QObject::connect(madeWithQt, SIGNAL(clicked()), qApp, SLOT(aboutQt()));
    QObject::connect(madeWithSFML, SIGNAL(clicked()), SFMLLicence, SLOT(show()));

    //Contributors
    leadDevelopper = new QLabel(tr("MAIN_DEVELOPPER", "Main developper and project manager : <span style=\"color:red;\">Martin Hammerchmidt alias Imote</span>"));
    allContributorsLayout = new QHBoxLayout;
    allContributorsOne = new QListWidget;
    allContributorsTwo = new QListWidget;
    allContributorsLayout->addWidget(allContributorsOne);
    allContributorsLayout->addWidget(allContributorsTwo);
    new QListWidgetItem("You <3", allContributorsOne);
    new QListWidgetItem("Krayon973", allContributorsTwo);
    new QListWidgetItem("Yohann Hammad", allContributorsOne);
    new QListWidgetItem("Si0ls", allContributorsTwo);
    new QListWidgetItem("Eldraeildor", allContributorsOne);
    new QListWidgetItem(tr("HAPPY4EVER", "And, don't forget to be Happy 4 Ever"), allContributorsOne);

    creditLayout->addWidget(openSourceText);
    creditLayout->addLayout(madeWithLayout);
    creditLayout->addWidget(leadDevelopper);
    creditLayout->addLayout(allContributorsLayout);
    creditLayout->addStretch();

    creditSection->setLayout(creditLayout);
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
    formGeneral->addRow(tr("RUN_ON_STARTUP"), runOnStartup);

    showNotifications = new QCheckBox();
    formGeneral->addRow(tr("SHOW_NOTIFICATION"), showNotifications);

    playSound = new QCheckBox();
    formGeneral->addRow(tr("PLAY_SOUND"), playSound);

    copyToClipboard = new QCheckBox();
    formGeneral->addRow(tr("COPY_FILE_LINK_CLIPBOARD"), copyToClipboard);

    lang = new QComboBox();
    lang->addItem("English");
    lang->addItem("Français");
    formGeneral->addRow(tr("APPLICATION_LANG", "Application's lang :"), lang);

    onlineServicesLayout = new QVBoxLayout;

    FTPLayout = new QHBoxLayout;
    FTPMethod = new QRadioButton(tr("USE_FTP"));
    configureFTPButton = new QPushButton(tr("CONFIGURE_FTP"));
    FTPLayout->addWidget(FTPMethod);
    FTPLayout->addWidget(configureFTPButton);

    HTTPLayout = new QVBoxLayout;
    HTTPLayoutForRadioAndPushButton = new QHBoxLayout;
    HTTPMethod = new QRadioButton(tr("USE_HTTP"));
    configureHTTPButton = new QPushButton(tr("CONFIGURE_HTTP"));
    HTTPLayoutForRadioAndPushButton->addWidget(HTTPMethod);
    HTTPLayoutForRadioAndPushButton->addWidget(configureHTTPButton);
    HTTPWarning = new QLabel(tr("ONLY_ADVANCED_USERS", "<font size='2'><span style='color:blue;'>(!)</span> Only for advanced users</font>"));
    HTTPLayout->addLayout(HTTPLayoutForRadioAndPushButton);
    HTTPLayout->addWidget(HTTPWarning);

    onlineServicesLayout->addLayout(FTPLayout);
    onlineServicesLayout->addLayout(HTTPLayout);

    onlineServices = new QGroupBox(tr("ONLINE_SERVICES_GROUPBOX"));
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

    windowContent->addTab(generalSection, tr("GENERAL", "Configuration menu, general section"));
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
    std::cerr << "AA";

#ifdef _WIN32
    /*QSettings startSettings("HKEY_CURRENT_USER\Software\Microsoft\Windows\CurrentVersion\Run");
        if (checked)
            startSettings.setValue("MyAppli", "aa");//QCoreApplication::applicationFilePath().replace('/','\\'));
         else
            startSettings.remove("MyAppli");

        std::cerr << "AA";*/
#endif
}

void ConfigurationWindows::showNotificationSettingModified(bool checked)
{
    settings.setValue(showNotificationsSettingName, checked);
}

void ConfigurationWindows::playSoundSettingModified(bool checked)
{
    settings.setValue(playSoundSettingName, checked);
}

void ConfigurationWindows::copyToClipboardSettingModified(bool checked)
{
    settings.setValue(copyToClipboardSettingName, checked);
}

void ConfigurationWindows::langSettingModified(QString newValue)
{
    settings.setValue(langSettingName, newValue);

    if(newValue == "English")
        QMessageBox::information(this, windowTitle, "You need to restart Uplimg.");
    else if(newValue == "Français")
        QMessageBox::information(this, windowTitle, "Vous devez redémarrer Uplimg.");
}

void ConfigurationWindows::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}

ConfigurationWindows::~ConfigurationWindows()
{
    delete FTPConf;
    delete HTTPConf;
}

void ConfigurationWindows::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_E)
        emit easterEgg();

}
