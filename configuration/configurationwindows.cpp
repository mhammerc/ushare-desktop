#include "configurationwindows.h"
#include "systemtrayicon.h"


ConfigurationWindows::ConfigurationWindows(SystemTrayIcon * parent, QWidget *qwidget) :
    QWidget(qwidget), windowTitle(tr("UPLIMG_CONFIGURATION"))
{
    this->parent = parent;
    QObject::connect(this, SIGNAL(easterEgg()), parent, SLOT(enableEasterEgg()));

    this->setWindowIcon(QIcon(":/icon/base.png"));
    this->setWindowTitle(windowTitle);

    this->setUpUI();

    this->setFixedSize(530, 380);

    /* Load Settings */
    runOnStartup->setChecked(settings.value(Reg::runOnStartup, true).toBool());
    showNotifications->setChecked(settings.value(Reg::showNotifications, true).toBool());
    playSound->setChecked(settings.value(Reg::playSound, true).toBool());
    copyToClipboard->setChecked(settings.value(Reg::copyToClipboard, true).toBool());
    autoOpenToBrowser->setChecked(settings.value(Reg::autoOpenToBrowser, true).toBool());
    lang->setCurrentText(settings.value(Reg::lang).toString());
    localSave->setChecked(settings.value(Reg::localSave).toBool());
    localSavePath->setText(settings.value(Reg::localSavePath).toString());
    imageType->setCurrentText(settings.value(Reg::imageFormat, "PNG").toString());
    imageQuality->setValue(settings.value(Reg::imageQuality, 100).toInt());
    imageQualityShower->setNum(settings.value(Reg::imageQuality, 100).toInt());

    takeFullScreenShortcut->setText(settings.value(Reg::takeFullScrenShortcut).toString());
    takeSelectedScreenShortcut->setText(settings.value(Reg::takeSelectedAreaScreenShortcut).toString());
    uploadFileShortcut->setText(settings.value(Reg::uploadFileShortcut).toString());
    uploadClipboardShortcut->setText(settings.value(Reg::uploadClipboardShortcut).toString());

    if(!settings.value(Reg::localSave).toBool())
        {
            localSavePath->setDisabled(true);
            localSavePathChooser->setDisabled(true);
        }

    if(settings.value(Reg::imageFormat).toString() != "JPEG")
        imageQuality->setDisabled(true);

    if (settings.value(Reg::choosedMethod).toString() == "FTP")
        FTPMethod->setChecked(true);
    else if (settings.value(Reg::choosedMethod).toString() == "HTTP")
        HTTPMethod->setChecked(true);
    else if(settings.value(Reg::choosedMethod).toString() == "LOCAL")
        localMethod->setChecked(true);

    if(settings.value(Reg::choosedMethod).toString() != "LOCAL")
        {
            localMethodPath->setDisabled(true);
            localMethodPathChooser->setDisabled(true);
        }

    if(settings.value(Reg::lang).toString().isNull())
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

    localMethodPath->setText(settings.value(Reg::localSavePath).toString());

    selectingAreaColor.setRed(settings.value(Reg::redArea).toInt());
    selectingAreaColor.setGreen(settings.value(Reg::greenArea).toInt());
    selectingAreaColor.setBlue(settings.value(Reg::blueArea).toInt());
    selectingAreaColorRandomizer(settings.value(Reg::randomizeArea).toBool());

    QPalette pal;
    pal.setColor(QPalette::Window, selectingAreaColor);
    selectingAreaColorShower->setPalette(pal);

    QObject::connect(windowContent, SIGNAL(currentChanged(int)), this, SLOT(currentTabChanged(int)));
#ifdef _WIN32
    QObject::connect(runOnStartup, SIGNAL(toggled(bool)), this, SLOT(runOnStartupSettingModified(bool)));
#endif
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
    QObject::connect(selectingAreaColorOpener, SIGNAL(clicked()), this, SLOT(selectingAreaColorClicked()));
    QObject::connect(selectingAreaColorRandomize, SIGNAL(toggled(bool)), this, SLOT(selectingAreaColorRandomizer(bool)));

    QObject::connect(localMethod, SIGNAL(toggled(bool)), this, SLOT(localMethodSettingsModified(bool)));
    QObject::connect(localMethodPath, SIGNAL(textChanged(QString)), this, SLOT(localMethodPathSettingsModified(QString)));
    QObject::connect(localMethodPathChooser, SIGNAL(clicked()), this, SLOT(localMethodPathSettingsClicked()));
    QObject::connect(FTPMethod, SIGNAL(toggled(bool)), this, SLOT(FTPMethodSettingModified(bool)));
    QObject::connect(HTTPMethod, SIGNAL(toggled(bool)), this, SLOT(HTTPMethodSettingModified(bool)));

    QObject::connect(configureFTPButton, SIGNAL(clicked()), this, SLOT(configureFTP()));
    QObject::connect(configureHTTPButton, SIGNAL(clicked()), this, SLOT(configureHTTP()));

    QObject::connect(takeFullScreenShortcut, SIGNAL(textChanged(QString)), this, SLOT(takeFullScreenShortcutChanged(QString)));
    QObject::connect(takeSelectedScreenShortcut, SIGNAL(textChanged(QString)), this, SLOT(takeSelectedAreaScreenShortcutChanged(QString)));
    QObject::connect(uploadFileShortcut, SIGNAL(textChanged(QString)), this, SLOT(uploadFileShortcutChanged(QString)));
    QObject::connect(uploadClipboardShortcut, SIGNAL(textChanged(QString)), this, SLOT(uploadClipboardShortcutChanged(QString)));

    QObject::connect(validateGeneral, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(validateUpload, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(validateHotkeys, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(validateCredit, SIGNAL(clicked()), this, SLOT(hide()));

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
    new QListWidgetItem("si0ls", allContributorsTwo);
    new QListWidgetItem("Yohann Hammad", allContributorsOne);
    new QListWidgetItem("Krayon973", allContributorsTwo);
    new QListWidgetItem("Eldraeildor", allContributorsOne);
    new QListWidgetItem("Mrs025", allContributorsTwo);
    happy4Ever = new QLabel(tr("HAPPY4EVER", "And, don't forget to be Happy 4 Ever"));

    validateCredit = new QPushButton("Ok");
    validateCreditLayout = new QHBoxLayout;
    validateCreditLayout->addStretch();
    validateCreditLayout->addWidget(validateCredit);

    creditLayout->addWidget(openSourceText);
    creditLayout->addLayout(madeWithLayout);
    creditLayout->addWidget(leadDevelopper);
    creditLayout->addLayout(allContributorsLayout);
    creditLayout->addWidget(happy4Ever);
    creditLayout->addStretch();
    creditLayout->addLayout(validateCreditLayout);

    creditSection->setLayout(creditLayout);
    windowContent->addTab(creditSection, tr("Credits"));
}

void ConfigurationWindows::setUpGeneralSectionUI()
{
    generalSection = new QWidget;
    generalLayout = new QVBoxLayout;

    //General settings
    generalSettings = new QGroupBox(tr("GENERAL_SETTINGS"));
    generalFormLayout = new QFormLayout;
#ifdef _WIN32
    runOnStartup = new QCheckBox;
    generalFormLayout->addRow(tr("RUN_ON_STARTUP"), runOnStartup);
#endif

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

    selectingAreaColorLayout = new QHBoxLayout;
    selectingAreaColorShower = new QLabel;
    selectingAreaColorShower->setAutoFillBackground(true);
    selectingAreaColorShower->setFixedWidth(50);
    selectingAreaColorOpener = new QPushButton("..");
    selectingAreaColorOpener->setFixedWidth(30);
    selectingAreaColorRandomize = new QCheckBox(tr("RANDOMIZE_COLOR"));
    selectingAreaColorLayout->addWidget(selectingAreaColorShower);
    selectingAreaColorLayout->addWidget(selectingAreaColorOpener);
    selectingAreaColorLayout->addWidget(selectingAreaColorRandomize);
    generalFormLayout->addRow(tr("CHOOSE_COLOR_FOR_SELECTING_AREA_SCREEN"), selectingAreaColorLayout);

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

    validateGeneral = new QPushButton("Ok");
    validateGeneralLayout = new QHBoxLayout;
    validateGeneralLayout->addStretch();
    validateGeneralLayout->addWidget(validateGeneral);

    generalLayout->addStretch();
    generalLayout->addLayout(validateGeneralLayout);

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

    validateUpload = new QPushButton("Ok");
    validateUploadLayout = new QHBoxLayout;
    validateUploadLayout->addStretch();
    validateUploadLayout->addWidget(validateUpload);

    uploadLayout->addWidget(onlineServices);
    uploadLayout->addStretch();
    uploadLayout->addLayout(validateUploadLayout);

    uploadSection->setLayout(uploadLayout);

    windowContent->addTab(uploadSection, tr("UPLOAD_SECTION"));
}

void ConfigurationWindows::setUpHotkeysSectionUI()
{
    hotkeysSection = new QWidget;
    hotkeysLayout = new QVBoxLayout;
    hotkeysGroupBox = new QGroupBox(tr("KEYBOARD_CONFIGURATION"));
    hotkeysIntermediateGroupBox = new QGroupBox;
    hotkeysBindingLayout = new QVBoxLayout;
    hotkeysFormLayout = new QFormLayout;

    hotkeysWelcomeText = new QLabel(tr("HOTKEYS_WELCOME_TEXT"));
    warningHotkeysDisabled = new QLabel(tr("WARNING_HOTKEYS_DISABLED"));

    takeFullScreenShortcut = new ShortcutGetter;
    takeSelectedScreenShortcut = new ShortcutGetter;
    uploadFileShortcut = new ShortcutGetter;
    uploadClipboardShortcut = new ShortcutGetter;

    hotkeysFormLayout->addRow(tr("TAKE_FULL_SCREEN_HOTKEYS"), takeFullScreenShortcut);
    hotkeysFormLayout->addRow(tr("TAKE_SELECTED_SCREEN_HOTKEYS"), takeSelectedScreenShortcut);
    hotkeysFormLayout->addRow(tr("UPLOAD_FILE_SHORTCUT"), uploadFileShortcut);
    hotkeysFormLayout->addRow(tr("UPLOAD_CLIPBOARD_SHORTCUT"), uploadClipboardShortcut);

    validateHotkeys = new QPushButton("Ok");
    validateHotkeysLayout = new QHBoxLayout;
    validateHotkeysLayout->addStretch();
    validateHotkeysLayout->addWidget(validateHotkeys);

    hotkeysIntermediateGroupBox->setLayout(hotkeysFormLayout);

    hotkeysBindingLayout->addWidget(hotkeysWelcomeText);
    hotkeysBindingLayout->addWidget(hotkeysIntermediateGroupBox);

    hotkeysGroupBox->setLayout(hotkeysBindingLayout);

    hotkeysLayout->addWidget(hotkeysGroupBox);
    hotkeysLayout->addWidget(warningHotkeysDisabled);
    hotkeysLayout->addStretch();
    hotkeysLayout->addLayout(validateHotkeysLayout);

    hotkeysSection->setLayout(hotkeysLayout);

    windowContent->addTab(hotkeysSection, tr("HOTKEYS_SECTION"));
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

    settings.setValue(Reg::choosedMethod, "FTP");
}

void ConfigurationWindows::HTTPMethodSettingModified(bool checked)
{
    if (!checked)
        return;

    settings.setValue(Reg::choosedMethod, "HTTP");
}

void ConfigurationWindows::runOnStartupSettingModified(bool checked)
{
    settings.setValue(Reg::runOnStartup, checked);

#ifdef _WIN32
    QSettings startSettings("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run", QSettings::NativeFormat);
    if (checked)
        startSettings.setValue("Uplimg", QCoreApplication::applicationFilePath().replace('/','\\'));
    else
        startSettings.remove("Uplimg");
#endif
}

void ConfigurationWindows::showNotificationSettingModified(bool checked)
{
    settings.setValue(Reg::showNotifications, checked);
}

void ConfigurationWindows::playSoundSettingModified(bool checked)
{
    settings.setValue(Reg::playSound, checked);
}

void ConfigurationWindows::copyToClipboardSettingModified(bool checked)
{
    settings.setValue(Reg::copyToClipboard, checked);
}

void ConfigurationWindows::langSettingModified(QString newValue)
{
    settings.setValue(Reg::lang, newValue);

    if(newValue == "English")
        QMessageBox::information(this, windowTitle, "You need to restart Uplimg.");
    else if(newValue == "Français")
        QMessageBox::information(this, windowTitle, "Vous devez redémarrer Uplimg.");
}

void ConfigurationWindows::autoOpenToBrowserSettingModified(bool checked)
{
    settings.setValue(Reg::autoOpenToBrowser, checked);
}

void ConfigurationWindows::imageTypeSettingModified(QString text)
{
    settings.setValue(Reg::imageFormat, text);
    if(text == "JPEG")
        imageQuality->setEnabled(true);
    else
        imageQuality->setDisabled(true);
}

void ConfigurationWindows::imageQualitySettingModified(int value)
{
    settings.setValue(Reg::imageQuality, value);
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

void ConfigurationWindows::hideEvent(QHideEvent *event)
{
    parent->enableHotkeys();
    event->accept();
}

void ConfigurationWindows::keyPressEvent(QKeyEvent * event)
{
    if(event->key() == Qt::Key_E)
        emit easterEgg();

}

void ConfigurationWindows::localSaveSettingsModified(bool checked)
{
    settings.setValue(Reg::localSave, checked);
    localSavePath->setEnabled(checked);
    localSavePathChooser->setEnabled(checked);
}

void ConfigurationWindows::localSavePathSettingsModified(QString path)
{
    settings.setValue(Reg::localSavePath, path);
    localMethodPath->setText(path);
}

void ConfigurationWindows::localSavePathSettingsClicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("CHOOSE_DIRECTORY"), localSavePath->text());
    localSavePath->setText(path);
    settings.setValue(Reg::localSavePath, path);
}

void ConfigurationWindows::localMethodSettingsModified(bool checked)
{
    localMethodPath->setEnabled(checked);
    localMethodPathChooser->setEnabled(checked);

    if(checked)
        settings.setValue(Reg::choosedMethod, "LOCAL");
}

void ConfigurationWindows::localMethodPathSettingsModified(QString path)
{
    settings.setValue(Reg::localSavePath, path);
    localSavePath->setText(path);
}

void ConfigurationWindows::localMethodPathSettingsClicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("CHOOSE_DIRECTORY"), localSavePath->text());
    localSavePath->setText(path);
    localMethodPath->setText(path);
    settings.setValue(Reg::localSavePath, path);
}

void ConfigurationWindows::selectingAreaColorClicked()
{
    QColor tempColor = QColorDialog::getColor(selectingAreaColor, this);

    if(!tempColor.isValid())
        return;
    selectingAreaColor = tempColor;

    QPalette pal;
    pal.setColor(QPalette::Window, selectingAreaColor);
    selectingAreaColorShower->setPalette(pal);

    settings.setValue(Reg::redArea, selectingAreaColor.red());
    settings.setValue(Reg::greenArea, selectingAreaColor.green());
    settings.setValue(Reg::blueArea, selectingAreaColor.blue());
}

void ConfigurationWindows::selectingAreaColorRandomizer(bool checked)
{
    selectingAreaColorRandomize->setChecked(checked);

    if(checked)
        selectingAreaColorOpener->setDisabled(true);
    else
        selectingAreaColorOpener->setEnabled(true);

    settings.setValue(Reg::randomizeArea, checked);
}

void ConfigurationWindows::takeFullScreenShortcutChanged(QString shortcut)
{
    settings.setValue(Reg::takeFullScrenShortcut, shortcut);
    parent->takeFullScreenShortcutChanged(shortcut);
}

void ConfigurationWindows::takeSelectedAreaScreenShortcutChanged(QString shortcut)
{
    settings.setValue(Reg::takeSelectedAreaScreenShortcut, shortcut);
    parent->takeSelectedAreaScreenShortcutChanged(shortcut);
}

void ConfigurationWindows::uploadFileShortcutChanged(QString shortcut)
{
    settings.setValue(Reg::uploadFileShortcut, shortcut);
    parent->uploadFileShortcutChanged(shortcut);
}

void ConfigurationWindows::uploadClipboardShortcutChanged(QString shortcut)
{
    settings.setValue(Reg::uploadClipboardShortcut, shortcut);
    parent->uploadClipboardShortcutChanged(shortcut);
}

void ConfigurationWindows::currentTabChanged(int index)
{
    if(index == 2)
        parent->disableHotkeys();
    else
        parent->enableHotkeys();
}

void ConfigurationWindows::resetTab()
{
    windowContent->setCurrentIndex(0);
}
