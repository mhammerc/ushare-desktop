#include "systemtrayicon.h"

SystemTrayIcon::SystemTrayIcon(QObject *qobject) :
    QSystemTrayIcon(qobject),
    applicationName("Uplimg"),
    HTTPWebPathSettingName("configuration/http/webPath"),
    FTPWebPathSettingName("configuration/ftp/webPath"),
    runOnStartupSettingName("configuration/runOnStartup"),
    choosedMethodSettingName("configuration/method"),
    showNotificationsSettingName("configuration/showNotifications"),
    playSoundSettingName("configuration/playSound"),
    copyToClipboardSettingName("configuration/clipboard"),
    takeFullScrenShortcutSettingName("configuration/shortcut/takeFullScreen"),
    takeSelectedAreaScreenShortcutSettingName("configuration/shortcut/takeSelectedArea"),
    uploadFileShortcutSettingName("configuration/shortcut/uploadFile"),
    uploadClipboardShortcutSettingName("configuration/shortcut/uploadClipboard"),
    autoOpenToBrowserSettingName("configuration/autoOpenToBrowser"),
    imageFormatSettingName("configuration/imageType"),
    imageQualitySettingName("configuration/imageQuality"),
    localSaveSettingName("configuration/localSave"),
    localSavePathSettingName("configuration/localSavePath"),
    linkFromSettingName("configuration/http/linkFrom")
{
    if(settings.value(runOnStartupSettingName).isNull()) //First time the application is started
        firstStart();

    fileSendedSound = new QSound(":/fileSended.wav", this);

    configurationWindows = 0;

    screenManager = new ScreenManager(this);
    setIcon(QIcon {":/small.png"});
    setToolTip(tr("DAEMON_RUNNING"));

    takeFullScreenKeySequence = QKeySequence(settings.value(takeFullScrenShortcutSettingName).toString());
    takeSelectedAreaKeySequence = QKeySequence(settings.value(takeSelectedAreaScreenShortcutSettingName).toString());
    uploadFileKeySequence = QKeySequence::fromString(settings.value(uploadFileShortcutSettingName).toString());
    uploadClipboardKeySequence = QKeySequence::fromString(settings.value(uploadClipboardShortcutSettingName).toString());

    takeFullScrenShortcut = new QxtGlobalShortcut(takeFullScreenKeySequence, this);
    takeSelectedAreaScreenShortcut = new QxtGlobalShortcut(takeSelectedAreaKeySequence, this);
    uploadFileShortcut = new QxtGlobalShortcut(uploadFileKeySequence, this);
    uploadClipboardShortcut = new QxtGlobalShortcut(uploadClipboardKeySequence, this);

    setUpContextMenu();

    QObject::connect(takeScreen, SIGNAL(triggered()), this, SLOT(takeFullScrenTriggered()));
    QObject::connect(takeSelectedScreen, SIGNAL(triggered()), this, SLOT(takeSelectedAreaScreenTriggered()));
    QObject::connect(uploadFile, SIGNAL(triggered()), this, SLOT(uploadSelectedFileTriggered()));
    QObject::connect(uploadClipboard, SIGNAL(triggered()), this, SLOT(uploadClipboardTriggered()));
    QObject::connect(showConfiguration, SIGNAL(triggered()), this, SLOT(showWindowConfigurationTriggered()));
    QObject::connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    QObject::connect(this, SIGNAL(messageClicked()), this, SLOT(openLastUrl()));
    QObject::connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(activatedTrigerred(QSystemTrayIcon::ActivationReason)));

    QObject::connect(takeFullScrenShortcut, SIGNAL(activated()), this, SLOT(takeFullScrenTriggered()));
    QObject::connect(takeSelectedAreaScreenShortcut, SIGNAL(activated()), this, SLOT(takeSelectedAreaScreenTriggered()));
    QObject::connect(uploadFileShortcut, SIGNAL(activated()), this, SLOT(uploadSelectedFileTriggered()));
    QObject::connect(uploadClipboardShortcut, SIGNAL(activated()), this, SLOT(uploadClipboardTriggered()));
}

void SystemTrayIcon::setUpContextMenu()
{
    systemTrayMenu = new QMenu;

    takeScreen = systemTrayMenu->addAction(tr("TAKE_NEW_FULLSCREEN"));
    takeSelectedScreen = systemTrayMenu->addAction(tr("TAKE_NEW_AREA_SELECTED_SCREEN"));
    uploadFile = systemTrayMenu->addAction(tr("UPLOAD_CHOOSED_FILE"));
    uploadClipboard = systemTrayMenu->addAction(tr("UPLOAD_CLIPBOARD"));
    systemTrayMenu->addSeparator();
    showConfiguration = systemTrayMenu->addAction(tr("CONFIGURATION", "In system tray icon"));
    quit = systemTrayMenu->addAction(tr("EXIT"));

    takeScreen->setShortcut(takeFullScrenShortcut->shortcut());
    takeSelectedScreen->setShortcut(takeSelectedAreaScreenShortcut->shortcut());
    uploadFile->setShortcut(uploadFileShortcut->shortcut());
    uploadClipboard->setShortcut(uploadClipboardShortcut->shortcut());

    systemTrayMenu->setTearOffEnabled(true);

    setContextMenu(systemTrayMenu);
}

void SystemTrayIcon::takeSelectedAreaScreenTriggered()
{
    fileName = getNewFileName(getImageFormat());
    pathToFile = getFileTempPath(fileName);
    screenManager->captureSelectedZone(pathToFile);
}

void SystemTrayIcon::sendSelectedArea()
{
    if (screenManager->autoSendFile(pathToFile))
        fileSended(fileName);
    else
        throwErrorAlert(Uplimg::ErrorList::UPLOAD_FAIL);
}

void SystemTrayIcon::takeFullScrenTriggered()
{
    QString fileName = getNewFileName(getImageFormat());
    QString pathToFile = getFileTempPath(fileName);

    if (screenManager->autoSendFile(screenManager->captureFullScreen(pathToFile)))
        fileSended(fileName);
    else
        throwErrorAlert(Uplimg::ErrorList::UPLOAD_FAIL);
}

void SystemTrayIcon::uploadSelectedFileTriggered()
{
    QString path = FileDialog::getOpenFileName(0, tr("SELECT_FILE"));

    if(!path.isNull())
        {
            if (screenManager->autoSendFile(path))
                {
                    QFileInfo fileInfo(path);
                    fileSended(fileInfo.fileName());
                }
            else
                throwErrorAlert(Uplimg::ErrorList::UPLOAD_FAIL);
        }
}

void SystemTrayIcon::fileSended(QString fileName)
{
    if(getUploadMethod() != Uplimg::UploadMethod::LOCAL && getUploadMethod() != Uplimg::UploadMethod::ERROR)
        {
            if(settings.value(playSoundSettingName).toBool())
                fileSendedSound->play();

            if(settings.value(linkFromSettingName).toString() != "FROM_HTTP" || getUploadMethod() != Uplimg::UploadMethod::HTTP)
                {
                    const QString urlPath = getUploadedFileURL(fileName);
                    lastUrl.setUrl(urlPath);
                }

            if(settings.value(autoOpenToBrowserSettingName).toBool())
                openLastUrl();

            if(settings.value(copyToClipboardSettingName).toBool())
                QApplication::clipboard()->setText(lastUrl.toString());

            if(settings.value(showNotificationsSettingName).toBool())
                this->showMessage(applicationName, tr("UPLOAD_SUCCESS_WITH_URL", "Congratulation !\nUpload success. The URL is :\n") + lastUrl.toString());
        }
    else if(getUploadMethod() == Uplimg::UploadMethod::LOCAL)
        {
            if(settings.value(playSoundSettingName).toBool())
                fileSendedSound->play();

            if(settings.value(showNotificationsSettingName).toBool())
                this->showMessage(applicationName, tr("UPLOAD_SUCCESS_LOCAL"));
        }
}

void SystemTrayIcon::uploadClipboardTriggered()
{
    const QString fileName = getNewFileName(".txt");
    const QString filePath = getFileTempPath(fileName);
    std::ofstream file(filePath.toStdString().c_str());

    if (file)
        {
            file << QApplication::clipboard()->text().toStdString();
            file.close();
            if (screenManager->autoSendFile(filePath))
                fileSended(fileName);
            else
                throwErrorAlert(Uplimg::ErrorList::UPLOAD_FAIL);
        }
}

QString SystemTrayIcon::getNewFileName(Uplimg::ImageFormat ending)
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();

    QString fileName = QString::number(date.dayOfYear())
                       + QString::number(time.hour())
                       + QString::number(time.minute())
                       + QString::number(time.second());

    if(ending == Uplimg::ImageFormat::PNG)
        return fileName + ".png";
    else if(ending == Uplimg::ImageFormat::JPEG)
        return fileName + ".jpg";
    else
        return fileName;

}


QString SystemTrayIcon::getNewFileName(QString ending)
{
    QTime time = QTime::currentTime();
    QDate date = QDate::currentDate();

    return QString::number(date.dayOfYear())
           + QString::number(time.hour())
           + QString::number(time.minute())
           + QString::number(time.second())
           + ending;
}

QString SystemTrayIcon::getFileTempPath(const QString &screenName)
{
    if(settings.value(localSaveSettingName).toBool() || settings.value(choosedMethodSettingName).toString() == "LOCAL")
        return settings.value(localSavePathSettingName).toString() + "/" + screenName;
    else
        return QStandardPaths::writableLocation(QStandardPaths::TempLocation)
               + "/"
               + screenName;
}

QString SystemTrayIcon::getUploadedFileURL(const QString &fileName)
{
    if(getUploadMethod() == Uplimg::UploadMethod::FTP)
        return settings.value(FTPWebPathSettingName, "http://").toString() + fileName;
    else if(getUploadMethod() == Uplimg::UploadMethod::HTTP)
        return settings.value(HTTPWebPathSettingName, "http://").toString() + fileName;
    else
        return "error";
}

void SystemTrayIcon::showWindowConfigurationTriggered()
{
    if(configurationWindows == 0)
        configurationWindows = new ConfigurationWindows(this);
    configurationWindows->show();
    configurationWindows->setWindowState(Qt::WindowActive);
}

void SystemTrayIcon::throwErrorAlert(const QString &text)
{
    QMessageBox::critical(0, "Uplimg", text);
}

void SystemTrayIcon::throwErrorAlert(const Uplimg::ErrorList &error)
{
    if (error == Uplimg::ErrorList::UPLOAD_FAIL)
        {
            const QString text(tr("UPLOAD_FAILED", "Upload failed.\nYou must verify Uplimg's configuration or your Internet configuration to solve the problem."));
            this->showMessage(applicationName, text);
        }
    else if(error == Uplimg::ErrorList::UPLOAD_METHOD_NOT_CHOOSED)
        {
            const QString text(tr("NO_METHOD_TO_UPLOAD_CHOOSED", "We can't upload anything.\nYou must configure method to upload before."));
            this->showMessage(applicationName, text);
        }
}

Uplimg::UploadMethod SystemTrayIcon::getUploadMethod() const
{
    if (settings.value(choosedMethodSettingName).toString().toStdString() == "FTP")
        return Uplimg::UploadMethod::FTP;
    else if (settings.value(choosedMethodSettingName).toString().toStdString() == "HTTP")
        return Uplimg::UploadMethod::HTTP;
    else if (settings.value(choosedMethodSettingName).toString().toStdString() == "LOCAL")
        return Uplimg::UploadMethod::LOCAL;
    else
        return Uplimg::UploadMethod::ERROR;
}

void SystemTrayIcon::firstStart()
{
    settings.setValue(runOnStartupSettingName, true);
    settings.setValue(showNotificationsSettingName, true);
    settings.setValue(playSoundSettingName, true);
    settings.setValue(copyToClipboardSettingName, true);
    settings.setValue(choosedMethodSettingName, "FTP");
    settings.setValue(takeFullScrenShortcutSettingName, "Alt+1");
    settings.setValue(takeSelectedAreaScreenShortcutSettingName, "Alt+2");
    settings.setValue(uploadFileShortcutSettingName, "Alt+3");
    settings.setValue(uploadClipboardShortcutSettingName, "Alt+4");
    settings.setValue(imageFormatSettingName, "PNG");
    settings.setValue(imageQualitySettingName, 100);
    settings.setValue(autoOpenToBrowserSettingName, false);
    settings.setValue(localSavePathSettingName, QStandardPaths::standardLocations(QStandardPaths::PicturesLocation));
    settings.setValue(localSaveSettingName, false);
}

SystemTrayIcon::~SystemTrayIcon()
{
    configurationWindows->deleteLater();
}

void SystemTrayIcon::enableEasterEgg()
{
    if(fileSendedSound->fileName() != ":/Easter_Egg.wav")
        {
            fileSendedSound->deleteLater();
            fileSendedSound = new QSound(":/Easter_Egg.wav");
        }
}

void SystemTrayIcon::openLastUrl()
{
    if(!lastUrl.toString().isNull())
        QDesktopServices::openUrl(lastUrl);
}

void SystemTrayIcon::activatedTrigerred(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::ActivationReason::Trigger)
        this->openLastUrl();
}

Uplimg::ImageFormat SystemTrayIcon::getImageFormat() const
{
    if(settings.value(imageFormatSettingName).toString() == "PNG")
        return Uplimg::ImageFormat::PNG;
    else if(settings.value(imageFormatSettingName).toString() == "JPEG")
        return Uplimg::ImageFormat::JPEG;
    else
        return Uplimg::ImageFormat::INVALID_FORMAT;
}

int SystemTrayIcon::getImageQuality() const
{
    return settings.value(imageQualitySettingName).toInt();
}
