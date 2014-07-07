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
    choosedMethodSettingName("configuration/method"),
    autoOpenToBrowserSettingName("configuration/autoOpenToBrowser"),
    imageTypeSettingName("configuration/imageType"),
    imageQualitySettingName("configuration/imageQuality"),
    localSaveSettingName("configuration/localSave"),
    localSavePathSettingName("configuration/localSavePath"),
    localMethodSettingName("configuration/localMethod")
{
    this->parent = parent;
    QObject::connect(this, SIGNAL(easterEgg()), parent, SLOT(enableEasterEgg()));

    this->setWindowIcon(QIcon(":/small.png"));
    this->setWindowTitle(windowTitle);

    this->setUpUI();

    this->setFixedSize(530, 370);

    /* Load Settings */
    runOnStartup->setChecked(settings.value(runOnStartupSettingName, true).toBool());
    showNotifications->setChecked(settings.value(showNotificationsSettingName, true).toBool());
    playSound->setChecked(settings.value(playSoundSettingName, true).toBool());
    copyToClipboard->setChecked(settings.value(copyToClipboardSettingName, true).toBool());
    autoOpenToBrowser->setChecked(settings.value(autoOpenToBrowserSettingName, true).toBool());
    lang->setCurrentText(settings.value(langSettingName).toString());
    localSave->setChecked(settings.value(localSaveSettingName).toBool());
    localSavePath->setText(settings.value(localSavePathSettingName).toString());
    imageType->setCurrentText(settings.value(imageTypeSettingName, "PNG").toString());
    imageQuality->setValue(settings.value(imageQualitySettingName, 100).toInt());
    imageQualityShower->setNum(settings.value(imageQualitySettingName, 100).toInt());

    if(!settings.value(localSaveSettingName).toBool())
    {
        localSavePath->setDisabled(true);
        localSavePathChooser->setDisabled(true);
    }

    if(settings.value(imageTypeSettingName).toString() != "JPEG")
        imageQuality->setDisabled(true);

    if (settings.value(choosedMethodSettingName).toString() == "FTP")
        FTPMethod->setChecked(true);
    else if (settings.value(choosedMethodSettingName).toString() == "HTTP")
        HTTPMethod->setChecked(true);
    else if(settings.value(choosedMethodSettingName).toString() == "LOCAL")
        localMethod->setChecked(true);

    if(settings.value(choosedMethodSettingName).toString() != "LOCAL")
    {
        localMethodPath->setDisabled(true);
        localMethodPathChooser->setDisabled(true);
    }

    if(settings.value(langSettingName).toString().isNull())
    {
        QString locale = QLocale::system().name().section('_', 0, 0);
        if(locale == "fr")
        {
            lang->setCurrentText("Français");
        }
        else
        {
            lang->setCurrentText("English");
        }
    }

    localMethodPath->setText(settings.value(localSavePathSettingName).toString());

    /* Settings Modifier */
    QObject::connect(runOnStartup, SIGNAL(toggled(bool)), this, SLOT(runOnStartupSettingModified(bool)));
    QObject::connect(showNotifications, SIGNAL(toggled(bool)), this, SLOT(showNotificationSettingModified(bool)));
    QObject::connect(playSound, SIGNAL(toggled(bool)), this, SLOT(playSoundSettingModified(bool)));
    QObject::connect(copyToClipboard, SIGNAL(toggled(bool)), this, SLOT(copyToClipboardSettingModified(bool)));
    QObject::connect(lang, SIGNAL(currentTextChanged(QString)), this, SLOT(langSettingModified(QString)));
    QObject::connect(localSave, SIGNAL(toggled(bool)), this, SLOT(localSaveSettingsModified(bool)));
    QObject::connect(localSavePath, SIGNAL(textChanged(QString)), this, SLOT(localSavePathSettingsModified(QString)));
    QObject::connect(localSavePathChooser, SIGNAL(clicked()), this, SLOT(localSavePathSettingsClicked()));
    QObject::connect(autoOpenToBrowser, SIGNAL(toggled(bool)), this, SLOT(autoOpenToBrowserSettingModified(bool)));
    QObject::connect(imageType, SIGNAL(currentTextChanged(QString)), this, SLOT(imageTypeSettingModified(QString)));
    QObject::connect(imageQuality, SIGNAL(valueChanged(int)), this, SLOT(imageQualitySettingModified(int)));
    QObject::connect(imageQuality, SIGNAL(valueChanged(int)), imageQualityShower, SLOT(setNum(int)));

    QObject::connect(localMethod, SIGNAL(toggled(bool)), this, SLOT(localMethodSettingsModified(bool)));
    QObject::connect(localMethodPath, SIGNAL(textChanged(QString)), this, SLOT(localMethodPathSettingsModified(QString)));
    QObject::connect(localMethodPathChooser, SIGNAL(clicked()), this, SLOT(localMethodPathSettingsClicked()));
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
    this->setUpUploadSectionUI();
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

    LGPLLicence = new QTextEdit;
    QFile LGPLLicenceFile(":/lgpl-2.1.txt");
    LGPLLicenceFile.open(QIODevice::ReadOnly);
    LGPLLicence->setText(LGPLLicenceFile.readAll());
    LGPLLicence->setWindowTitle(tr("LGPL Licence"));
    LGPLLicence->setReadOnly(true);
    LGPLLicence->setFixedSize(400,450);

    madeWithLayout = new QHBoxLayout;
    madeWithSFML = new QPushButton(tr("MADE_WITH_SFML", "Made with the lightness of SFML"));
    madeWithQt = new QPushButton(tr("MADE_WITH_QT", "Made with the flexibility of Qt"));
    madeWithQxt = new QPushButton(tr("MADE_WITH_QXT", "Made with the powerfull of Qxt"));
    madeWithLayout->addWidget(madeWithSFML);
    madeWithLayout->addWidget(madeWithQt);
    madeWithLayout->addWidget(madeWithQxt);


    QObject::connect(madeWithSFML, SIGNAL(clicked()), SFMLLicence, SLOT(show()));
    QObject::connect(madeWithQt, SIGNAL(clicked()), qApp, SLOT(aboutQt()));
    QObject::connect(madeWithQxt, SIGNAL(clicked()), LGPLLicence, SLOT(show()));

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
    new QListWidgetItem("Mrs025", allContributorsTwo);
    happy4Ever = new QLabel(tr("HAPPY4EVER", "And, don't forget to be Happy 4 Ever"));

    creditLayout->addWidget(openSourceText);
    creditLayout->addLayout(madeWithLayout);
    creditLayout->addWidget(leadDevelopper);
    creditLayout->addLayout(allContributorsLayout);
    creditLayout->addWidget(happy4Ever);
    creditLayout->addStretch();

    creditSection->setLayout(creditLayout);
    windowContent->addTab(creditSection, tr("Credits"));
}

void ConfigurationWindows::setUpHotkeysSectionUI()
{
    hotkeysSection = new QWidget;
    windowContent->addTab(hotkeysSection, tr("HOTKEYS_SECTION"));
}

void ConfigurationWindows::setUpGeneralSectionUI()
{
    generalSection = new QWidget;
    generalLayout = new QVBoxLayout;

    //General settings
    generalSettings = new QGroupBox(tr("GENERAL_SETTINGS"));
    generalFormLayout = new QFormLayout;

    runOnStartup = new QCheckBox;
    generalFormLayout->addRow(tr("RUN_ON_STARTUP"), runOnStartup);

    lang = new QComboBox;
    lang->addItem("English");
    lang->addItem("Français");
    generalFormLayout->addRow(tr("APPLICATION_LANG", "Application's lang :"), lang);

    imageType = new QComboBox;
    imageType->addItem("PNG");
    imageType->addItem("JPEG");
    generalFormLayout->addRow(tr("IMAGE_TYPE"), imageType);

    imageQualityLayout = new QHBoxLayout;
    imageQuality = new QSlider(Qt::Horizontal);
    imageQuality->setMinimum(0);
    imageQuality->setMaximum(100);
    imageQualityShower = new QLabel("0");
    imageQualityLayout->addWidget(imageQuality);
    imageQualityLayout->addWidget(imageQualityShower);
    generalFormLayout->addRow(tr("IMAGE_QUALITY"), imageQualityLayout);

    localSaveLayout = new QHBoxLayout;
    localSave = new QCheckBox;
    localSavePath = new QLineEdit;
    localSavePathChooser = new QPushButton("..");
    localSavePathChooser->setFixedWidth(30);
    localSaveLayout->addWidget(localSave);
    localSaveLayout->addWidget(localSavePath);
    localSaveLayout->addWidget(localSavePathChooser);
    generalFormLayout->addRow(tr("LOCAL_SAVE"), localSaveLayout);

    generalSettings->setLayout(generalFormLayout);
    generalLayout->addWidget(generalSettings);

    //On sucess settings
    onSuccessSettings = new QGroupBox(tr("ON_SUCCESS"));
    onSuccessFormLayout = new QFormLayout;

    playSound = new QCheckBox;
    onSuccessFormLayout->addRow(tr("PLAY_SOUND"), playSound);

    showNotifications = new QCheckBox;
    onSuccessFormLayout->addRow(tr("SHOW_NOTIFICATION"), showNotifications);

    copyToClipboard = new QCheckBox;
    onSuccessFormLayout->addRow(tr("COPY_FILE_LINK_CLIPBOARD"), copyToClipboard);

    autoOpenToBrowser = new QCheckBox;
    onSuccessFormLayout->addRow(tr("AUTO_OPEN_FILE_IN_BROWSER"), autoOpenToBrowser);

    onSuccessSettings->setLayout(onSuccessFormLayout);
    generalLayout->addWidget(onSuccessSettings);

    validate = new QPushButton("Ok");
    validateLayout = new QHBoxLayout;
    validateLayout->addStretch();
    validateLayout->addWidget(validate);

    generalLayout->addStretch();
    generalLayout->addLayout(validateLayout);

    generalSection->setLayout(generalLayout);

    windowContent->addTab(generalSection, tr("GENERAL", "Configuration menu, general section"));
}

void ConfigurationWindows::setUpUploadSectionUI()
{
    uploadSection = new QWidget;
    uploadLayout = new QVBoxLayout;
    onlineServicesLayout = new QVBoxLayout;

    localMethodLayout = new QHBoxLayout;
    localMethod = new QRadioButton(tr("USE_UPLOADMETHOD_LOCAL"));
    localMethodPath = new QLineEdit;
    localMethodPathChooser = new QPushButton("..");
    localMethodPathChooser->setFixedWidth(30);
    localMethodLayout->addWidget(localMethod);
    localMethodLayout->addWidget(localMethodPath);
    localMethodLayout->addWidget(localMethodPathChooser);

    FTPLayout = new QHBoxLayout;
    FTPMethod = new QRadioButton(tr("USE_UPLOADMETHOD_FTP"));
    configureFTPButton = new QPushButton(tr("CONFIGURE_FTP"));
    FTPLayout->addWidget(FTPMethod);
    FTPLayout->addWidget(configureFTPButton);

    HTTPLayout = new QVBoxLayout;
    HTTPLayoutForRadioAndPushButton = new QHBoxLayout;
    HTTPMethod = new QRadioButton(tr("USE_UPLOADMETHOD_HTTP"));
    configureHTTPButton = new QPushButton(tr("CONFIGURE_HTTP"));
    HTTPLayoutForRadioAndPushButton->addWidget(HTTPMethod);
    HTTPLayoutForRadioAndPushButton->addWidget(configureHTTPButton);
    HTTPWarning = new QLabel(tr("ONLY_ADVANCED_USERS", "<font size='2'><span style='color:blue;'>(!)</span> Only for advanced users</font>"));
    HTTPLayout->addLayout(HTTPLayoutForRadioAndPushButton);
    HTTPLayout->addWidget(HTTPWarning);

    onlineServicesLayout->addLayout(localMethodLayout);
    onlineServicesLayout->addLayout(FTPLayout);
    onlineServicesLayout->addLayout(HTTPLayout);

    onlineServices = new QGroupBox(tr("ONLINE_SERVICES_GROUPBOX"));
    onlineServices->setLayout(onlineServicesLayout);

    uploadLayout->addWidget(onlineServices);
    uploadLayout->addStretch();

    uploadSection->setLayout(uploadLayout);

    windowContent->addTab(uploadSection, tr("UPLOAD_SECTION"));
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

void ConfigurationWindows::autoOpenToBrowserSettingModified(bool checked)
{
    settings.setValue(autoOpenToBrowserSettingName, checked);
}

void ConfigurationWindows::imageTypeSettingModified(QString text)
{
    settings.setValue(imageTypeSettingName, text);
    if(text == "JPEG")
        imageQuality->setEnabled(true);
    else
        imageQuality->setDisabled(true);
}

void ConfigurationWindows::imageQualitySettingModified(int value)
{
    settings.setValue(imageQualitySettingName, value);
}

void ConfigurationWindows::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}

ConfigurationWindows::~ConfigurationWindows()
{
    FTPConf->deleteLater();
    HTTPConf->deleteLater();
}

void ConfigurationWindows::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_E)
        emit easterEgg();

}

void ConfigurationWindows::localSaveSettingsModified(bool checked)
{
    settings.setValue(localSaveSettingName, checked);
    localSavePath->setEnabled(checked);
    localSavePathChooser->setEnabled(checked);
}

void ConfigurationWindows::localSavePathSettingsModified(QString path)
{
    settings.setValue(localSavePathSettingName, path);
    localMethodPath->setText(path);
}

void ConfigurationWindows::localSavePathSettingsClicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("CHOOSE_DIRECTORY"), localSavePath->text());
    localSavePath->setText(path);
    settings.setValue(localSavePathSettingName, path);
}

void ConfigurationWindows::localMethodSettingsModified(bool checked)
{
    settings.setValue(localMethodSettingName, checked);
    localMethodPath->setEnabled(checked);
    localMethodPathChooser->setEnabled(checked);

    if(checked)
        settings.setValue(choosedMethodSettingName, "LOCAL");
}

void ConfigurationWindows::localMethodPathSettingsModified(QString path)
{
    settings.setValue(localSavePathSettingName, path);
    localSavePath->setText(path);
}

void ConfigurationWindows::localMethodPathSettingsClicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("CHOOSE_DIRECTORY"), localSavePath->text());
    localSavePath->setText(path);
    localMethodPath->setText(path);
    settings.setValue(localSavePathSettingName, path);
}
