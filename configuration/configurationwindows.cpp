#include "configurationwindows.h"
#include "systemtrayicon.h"


ConfigurationWindows::ConfigurationWindows(SystemTrayIcon * parent, QWidget *qwidget) :
    QWidget(qwidget, Qt::WindowFlags(Qt::FramelessWindowHint | Qt::WindowMinMaxButtonsHint | Qt::WindowSystemMenuHint)), windowTitle(tr("UPLIMG_CONFIGURATION"))
{
    setContentsMargins(-10,-10,-10,-10);
    this->parent = parent;
    setObjectName("windowWithoutFrameBlack");
    QObject::connect(this, SIGNAL(easterEgg()), parent, SLOT(enableEasterEgg()));

    this->setWindowIcon(QIcon(":/icon/base.png"));
    this->setWindowTitle(windowTitle);

    updateManager = new QNetworkAccessManager(this);
    connect(updateManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(verifyUpdateFinished(QNetworkReply*)));

    this->setUpUI();

    /* Load Settings */
#ifdef _win32
    runOnStartup->setChecked(settings.value(Reg::runOnStartup, true).toBool());
#endif
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
    sendPasteShortcut->setText(settings.value(Reg::sendPasteShortcut).toString());
    uploadFileShortcut->setText(settings.value(Reg::uploadFileShortcut).toString());
    uploadClipboardShortcut->setText(settings.value(Reg::uploadClipboardShortcut).toString());

    if(!settings.value(Reg::localSave).toBool())
        {
            localSavePath->setDisabled(true);
            localSavePathChooser->setDisabled(true);
        }

    if(settings.value(Reg::imageFormat).toString() != "JPEG")
        imageQuality->setDisabled(true);

    if(settings.value(Reg::choosedMethod).toString() == "UPLIMG_WEB")
        uplimgWeb->setChecked(true);
    else if (settings.value(Reg::choosedMethod).toString() == "FTP")
        FTPMethod->setChecked(true);
    else if (settings.value(Reg::choosedMethod).toString() == "HTTP")
        HTTPMethod->setChecked(true);
    else if(settings.value(Reg::choosedMethod).toString() == "LOCAL")
        {
            localMethod->setChecked(true);
            localSave->setChecked(true);
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

    selectingAreaColor.setRed(settings.value(Reg::redArea).toInt());
    selectingAreaColor.setGreen(settings.value(Reg::greenArea).toInt());
    selectingAreaColor.setBlue(settings.value(Reg::blueArea).toInt());
    selectingAreaColorRandomizer(settings.value(Reg::randomizeArea).toBool());

    QPalette pal;
    pal.setColor(QPalette::Window, selectingAreaColor);
    selectingAreaColorShower->setPalette(pal);

    QObject::connect(topBarWidget, SIGNAL(minimize()), this, SLOT(showMinimized()));
    QObject::connect(topBarWidget, SIGNAL(close()), this, SLOT(close()));

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

    QObject::connect(verifyUpdatePushButton, SIGNAL(clicked()), this, SLOT(verifyUpdate()));
    QObject::connect(updatePushButton, SIGNAL(clicked()), this, SLOT(downloadUpdate()));

    QObject::connect(localMethod, SIGNAL(toggled(bool)), this, SLOT(localMethodSettingsModified(bool)));
    QObject::connect(uplimgWeb, SIGNAL(toggled(bool)), this, SLOT(uplimgWebMethodSettingModified(bool)));
    QObject::connect(FTPMethod, SIGNAL(toggled(bool)), this, SLOT(FTPMethodSettingModified(bool)));
    QObject::connect(HTTPMethod, SIGNAL(toggled(bool)), this, SLOT(HTTPMethodSettingModified(bool)));

    QObject::connect(configureFTPButton, SIGNAL(clicked()), this, SLOT(configureFTP()));
    QObject::connect(configureHTTPButton, SIGNAL(clicked()), this, SLOT(configureHTTP()));

    QObject::connect(takeFullScreenShortcut, SIGNAL(textChanged(QString)), this, SLOT(takeFullScreenShortcutChanged(QString)));
    QObject::connect(takeSelectedScreenShortcut, SIGNAL(textChanged(QString)), this, SLOT(takeSelectedAreaScreenShortcutChanged(QString)));
    QObject::connect(sendPasteShortcut, SIGNAL(textChanged(QString)), this, SLOT(sendPasteShortcutChanged(QString)));
    QObject::connect(uploadFileShortcut, SIGNAL(textChanged(QString)), this, SLOT(uploadFileShortcutChanged(QString)));
    QObject::connect(uploadClipboardShortcut, SIGNAL(textChanged(QString)), this, SLOT(uploadClipboardShortcutChanged(QString)));

    //QObject::connect(validate, SIGNAL(clicked()), this, SLOT(hide()));
    QObject::connect(bottomBar, SIGNAL(validate()), this, SLOT(refreshCSS()));

    FTPConf = new FTPConfiguration();
    HTTPConf = new HTTPConfiguration();

    this->setLayout(mainLayout);

    this->setFixedSize(530, this->minimumHeight());
}

void ConfigurationWindows::setUpUI()
{
    windowContent = new TabWidgetBlue;
    mainLayout = new QVBoxLayout;

    this->setUpTopBarUI();
    this->setUpGeneralSectionUI();
    this->setUpUploadSectionUI();
    this->setUpHotkeysSectionUI();
    this->setUpUpdateSectionUI();
    this->setUpCreditsSectionUI();


    bottomBar = new BottomBarConfigurationWindow;

    mainLayout->addWidget(topBarWidget);
    mainLayout->addWidget(windowContent);
    mainLayout->addWidget(bottomBar);
}

void ConfigurationWindows::setUpTopBarUI()
{
    topBarWidget = new TopBarWidget(this);
}

void ConfigurationWindows::setUpGeneralSectionUI()
{
    generalSection = new QWidget;
    generalLayout = new QVBoxLayout;

    //General settings
    generalSettings = new GroupBoxBlue(tr("GENERAL_SETTINGS"));
    generalFormLayout = new QFormLayout;
    generalFormLayout->setFormAlignment(Qt::AlignRight);
#ifdef _WIN32
    runOnStartup = new CheckBoxGreen;
    generalFormLayout->addRow(tr("RUN_ON_STARTUP"), runOnStartup);
#endif

    lang = new ComboBoxBlue;
    lang->addItem("English");
    lang->addItem("Français");
    generalFormLayout->addRow(tr("APPLICATION_LANG", "Application's lang :"), lang);

    selectingAreaColorLayout = new QHBoxLayout;
    selectingAreaColorShower = new LabelWithoutBackground;
    selectingAreaColorShower->setAutoFillBackground(true);
    selectingAreaColorShower->setFixedWidth(50);
    selectingAreaColorOpener = new ButtonBlue("..");
    selectingAreaColorOpener->setFixedWidth(30);
    selectingAreaColorRandomize = new CheckBoxGreen(tr("RANDOMIZE_COLOR"));
    selectingAreaColorLayout->addWidget(selectingAreaColorShower);
    selectingAreaColorLayout->addWidget(selectingAreaColorOpener);
    selectingAreaColorLayout->addWidget(selectingAreaColorRandomize);
    generalFormLayout->addRow(tr("CHOOSE_COLOR_FOR_SELECTING_AREA_SCREEN"), selectingAreaColorLayout);

    generalSettings->setLayout(generalFormLayout);
    generalLayout->addWidget(generalSettings);

    //On sucess settings
    onSuccessSettings = new GroupBoxBlue(tr("ON_SUCCESS"));
    onSuccessFormLayout = new QFormLayout;

    playSound = new CheckBoxGreen;
    onSuccessFormLayout->addRow(tr("PLAY_SOUND"), playSound);

    showNotifications = new CheckBoxGreen;
    onSuccessFormLayout->addRow(tr("SHOW_NOTIFICATION"), showNotifications);

    copyToClipboard = new CheckBoxGreen;
    onSuccessFormLayout->addRow(tr("COPY_FILE_LINK_CLIPBOARD"), copyToClipboard);

    autoOpenToBrowser = new CheckBoxGreen;
    onSuccessFormLayout->addRow(tr("AUTO_OPEN_FILE_IN_BROWSER"), autoOpenToBrowser);

    onSuccessSettings->setLayout(onSuccessFormLayout);
    generalLayout->addWidget(onSuccessSettings);
    generalLayout->addStretch();

    generalSection->setLayout(generalLayout);

    windowContent->addTab(generalSection, tr("GENERAL", "Configuration menu, general section"));
}

void ConfigurationWindows::setUpUploadSectionUI()
{
    uploadSection = new QWidget;
    uploadLayout = new QVBoxLayout;
    onlineServicesLayout = new QVBoxLayout;

    uplimgWeb = new RadioButtonGreen(tr("USE_UPLOADMETHOD_UPLIMGWEB"));
    localMethod = new RadioButtonGreen(tr("USE_UPLOADMETHOD_LOCAL"));

    FTPLayout = new QHBoxLayout;
    FTPMethod = new RadioButtonGreen(tr("USE_UPLOADMETHOD_FTP"));
    configureFTPButton = new ButtonBlue(tr("CONFIGURE_FTP"));
    FTPLayout->addWidget(FTPMethod);
    FTPLayout->addWidget(configureFTPButton);

    HTTPLayout = new QVBoxLayout;
    HTTPLayoutForRadioAndPushButton = new QHBoxLayout;
    HTTPMethod = new RadioButtonGreen(tr("USE_UPLOADMETHOD_HTTP"));
    configureHTTPButton = new ButtonBlue(tr("CONFIGURE_HTTP"));
    HTTPLayoutForRadioAndPushButton->addWidget(HTTPMethod);
    HTTPLayoutForRadioAndPushButton->addWidget(configureHTTPButton);
    HTTPWarning = new LabelRed(tr("ONLY_ADVANCED_USERS", "<font size='2'><span style='color:blue;'>(!)</span> Only for advanced users</font>"));
    HTTPLayout->addLayout(HTTPLayoutForRadioAndPushButton);
    HTTPLayout->addWidget(HTTPWarning);

    onlineServicesLayout->addWidget(uplimgWeb);
    onlineServicesLayout->addLayout(FTPLayout);
    onlineServicesLayout->addLayout(HTTPLayout);
    onlineServicesLayout->addWidget(localMethod);

    onlineServices = new GroupBoxBlue(tr("ONLINE_SERVICES_GROUPBOX"));
    onlineServices->setLayout(onlineServicesLayout);

    pictureLayout = new QFormLayout;

    imageType = new ComboBoxBlue;
    imageType->addItem("PNG");
    imageType->addItem("JPEG");
    pictureLayout->addRow(tr("IMAGE_TYPE"), imageType);

    imageQualityLayout = new QHBoxLayout;
    imageQuality = new SliderBlue(Qt::Horizontal);
    imageQuality->setMinimum(0);
    imageQuality->setMaximum(100);
    imageQualityShower = new LabelOrange("0");
    imageQualityLayout->addWidget(imageQuality);
    imageQualityLayout->addWidget(imageQualityShower);
    pictureLayout->addRow(tr("IMAGE_QUALITY"), imageQualityLayout);

    localSaveLayout = new QHBoxLayout;
    localSave = new CheckBoxGreen;
    localSavePath = new QLineEdit;
    localSavePathChooser = new ButtonBlue("..");
    localSavePathChooser->setFixedWidth(30);
    localSaveLayout->addWidget(localSave);
    localSaveLayout->addWidget(localSavePath);
    localSaveLayout->addWidget(localSavePathChooser);
    pictureLayout->addRow(tr("LOCAL_SAVE"), localSaveLayout);

    picture = new GroupBoxBlue(tr("PICTURE_GROUPBOX"));
    picture->setLayout(pictureLayout);

    uploadLayout->addWidget(onlineServices);
    uploadLayout->addWidget(picture);
    uploadLayout->addStretch();

    uploadSection->setLayout(uploadLayout);

    windowContent->addTab(uploadSection, tr("UPLOAD_SECTION"));
}

void ConfigurationWindows::setUpHotkeysSectionUI()
{
    hotkeysSection = new QWidget;
    hotkeysLayout = new QVBoxLayout;
    hotkeysGroupBox = new GroupBoxBlue(tr("KEYBOARD_CONFIGURATION"));
    hotkeysIntermediateGroupBox = new GroupBoxBlue;
    hotkeysBindingLayout = new QVBoxLayout;
    hotkeysFormLayout = new QFormLayout;

    hotkeysWelcomeText = new QLabel(tr("HOTKEYS_WELCOME_TEXT"));
    warningHotkeysDisabled = new LabelOrange(tr("WARNING_HOTKEYS_DISABLED"));

    takeFullScreenShortcut = new ShortcutGetter;
    takeSelectedScreenShortcut = new ShortcutGetter;
    sendPasteShortcut = new ShortcutGetter;
    uploadFileShortcut = new ShortcutGetter;
    uploadClipboardShortcut = new ShortcutGetter;

    hotkeysFormLayout->addRow(tr("TAKE_FULL_SCREEN_HOTKEYS"), takeFullScreenShortcut);
    hotkeysFormLayout->addRow(tr("TAKE_SELECTED_SCREEN_HOTKEYS"), takeSelectedScreenShortcut);
    hotkeysFormLayout->addRow(tr("SEND_PASTE_HOTKEYS"), sendPasteShortcut);
    hotkeysFormLayout->addRow(tr("UPLOAD_FILE_SHORTCUT"), uploadFileShortcut);
    hotkeysFormLayout->addRow(tr("UPLOAD_CLIPBOARD_SHORTCUT"), uploadClipboardShortcut);

    hotkeysIntermediateGroupBox->setLayout(hotkeysFormLayout);

    hotkeysBindingLayout->addWidget(hotkeysWelcomeText);
    hotkeysBindingLayout->addWidget(hotkeysIntermediateGroupBox);

    hotkeysGroupBox->setLayout(hotkeysBindingLayout);

    hotkeysLayout->addWidget(hotkeysGroupBox);
    hotkeysLayout->addWidget(warningHotkeysDisabled);
    hotkeysLayout->addStretch();

    hotkeysSection->setLayout(hotkeysLayout);

    windowContent->addTab(hotkeysSection, tr("HOTKEYS_SECTION"));
}

void ConfigurationWindows::setUpUpdateSectionUI()
{
    updateSection = new QWidget;
    updateMainLayout = new QVBoxLayout;
    updateGroupBox = new QGroupBox(tr("UPDATE_GROUPBOX"));
    updateLayout = new QHBoxLayout;
    updateVersionLayout = new QFormLayout;
    updateVersionLayout->addRow(new QLabel(tr("ACTUAL_VERSION")), new QLabel(Uplimg::version));
    lastVersion = new QLabel(Uplimg::version);
    updateVersionLayout->addRow(new QLabel(tr("LATEST_VERSION")), lastVersion);
    updateButtonLayout = new QVBoxLayout;
    verifyUpdatePushButton = new ButtonBlue(tr("VERIFY_NEW_VERSION"));
    updatePushButton = new ButtonBlue(tr("UPDATE_NOW"));
    updatePushButton->setDisabled(true);
    updateButtonLayout->addWidget(verifyUpdatePushButton);
    updateButtonLayout->addWidget(updatePushButton);

    updateLayout->addLayout(updateVersionLayout);
    updateLayout->addLayout(updateButtonLayout);
    updateGroupBox->setLayout(updateLayout);
    updateMainLayout->addWidget(updateGroupBox);
    updateMainLayout->addStretch();
    updateSection->setLayout(updateMainLayout);

    windowContent->addTab(updateSection, tr("UPDATE_SECTION"));

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
    madeWithSFML = new ButtonBlue(tr("MADE_WITH_SFML", "Made with the lightness of SFML"));
    madeWithQt = new ButtonBlue(tr("MADE_WITH_QT", "Made with the flexibility of Qt"));
    madeWithLayout->addStretch();
    madeWithLayout->addWidget(madeWithQt);
    madeWithLayout->addWidget(madeWithSFML);
    madeWithLayout->addStretch();

    QObject::connect(madeWithSFML, SIGNAL(clicked()), SFMLLicence, SLOT(show()));
    QObject::connect(madeWithQt, SIGNAL(clicked()), qApp, SLOT(aboutQt()));

    //Contributors
    leadDevelopper = new LabelOrange(tr("MAIN_DEVELOPPER"));
    si0ls = new LabelOrange(tr("SI0LS"));
    allContributorsLayout = new QHBoxLayout;
    allContributorsOne = new ListWidgetGreen;
    allContributorsTwo = new ListWidgetOrange;
    allContributorsLayout->addWidget(allContributorsOne);
    allContributorsLayout->addWidget(allContributorsTwo);
    new QListWidgetItem("You <3", allContributorsOne);
    new QListWidgetItem("si0ls", allContributorsTwo);
    new QListWidgetItem("Yohann Hammad", allContributorsOne);
    new QListWidgetItem("Krayon973", allContributorsTwo);
    new QListWidgetItem("Eldraeildor", allContributorsOne);
    new QListWidgetItem("Mrs025", allContributorsTwo);
    happy4Ever = new LabelBlue(tr("HAPPY4EVER"));

    creditLayout->addWidget(openSourceText);
    creditLayout->addLayout(madeWithLayout);
    creditLayout->addWidget(leadDevelopper);
    creditLayout->addWidget(si0ls);
    creditLayout->addLayout(allContributorsLayout);
    creditLayout->addWidget(happy4Ever);
    creditLayout->addStretch();

    creditSection->setLayout(creditLayout);
    windowContent->addTab(creditSection, tr("Credits"));
}

void ConfigurationWindows::configureFTP()
{
    FTPConf->show();
}

void ConfigurationWindows::configureHTTP()
{
    HTTPConf->show();
}

void ConfigurationWindows::refreshCSS()
{
    QFile css("styleSheet.css");
    css.open(QIODevice::ReadOnly);
    QString sheet(css.readAll());
    qApp->setStyleSheet(sheet);
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

void ConfigurationWindows::uplimgWebMethodSettingModified(bool checked)
{
    if(checked)
        settings.setValue(Reg::choosedMethod, "UPLIMG_WEB");
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
}

void ConfigurationWindows::localSavePathSettingsClicked()
{
    QString path = QFileDialog::getExistingDirectory(this, tr("CHOOSE_DIRECTORY"), localSavePath->text());
    localSavePath->setText(path);
    settings.setValue(Reg::localSavePath, path);
}

void ConfigurationWindows::localMethodSettingsModified(bool checked)
{
    if(checked)
        {
            settings.setValue(Reg::choosedMethod, "LOCAL");
            localSave->setChecked(true);
            localSave->setDisabled(true);
        }
    else
        {
            localSave->setEnabled(true);
        }
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

void ConfigurationWindows::sendPasteShortcutChanged(QString const &shortcut)
{
    settings.setValue(Reg::sendPasteShortcut, shortcut);
    parent->sendPasteShortcutChanged(shortcut);
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

void ConfigurationWindows::verifyUpdate()
{
    updateManager->get(QNetworkRequest(QUrl(Uplimg::updateVersionLink)));
}

void ConfigurationWindows::verifyUpdateFinished(QNetworkReply * reply)
{
    QByteArray array = reply->readLine();
    array = array.remove(array.length()-1, 1);
    lastVersion->setText(array);

    array = reply->readLine();
    array = array.remove(array.length()-1, 1);
    updateLink.setUrl(array);

    if(lastVersion->text() != Uplimg::version)
        updatePushButton->setEnabled(true);
}

void ConfigurationWindows::downloadUpdate()
{
    QDesktopServices::openUrl(updateLink);
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

void ConfigurationWindows::paintEvent(QPaintEvent *)
{
    QStyleOption opt;
    opt.init (this);
    QPainter p (this);
    style ()->drawPrimitive (QStyle::PE_Widget, &opt, &p, this);
}
