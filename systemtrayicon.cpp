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
    fileSendedSound(":/fileSended.wav")
{
    if(settings.value(runOnStartupSettingName).isNull()) //First time the application is started
        firstStart();

    configurationWindows = new ConfigurationWindows;

    screenManager = new ScreenManager(this);
    setIcon(QIcon {":/small.png"});
    setToolTip(tr("DAEMON_RUNNING"));

    setUpContextMenu();

    QObject::connect(takeScreen, SIGNAL(triggered()), this, SLOT(takeFullScrenTriggered()));
    QObject::connect(takeSelectedScreen, SIGNAL(triggered()), this, SLOT(takeSelectedAreaScreenTriggered()));
    QObject::connect(uploadFile, SIGNAL(triggered()), this, SLOT(uploadSelectedFileTriggered()));
    QObject::connect(uploadClipboard, SIGNAL(triggered()), this, SLOT(uploadClipboardTriggered()));
    QObject::connect(showConfiguration, SIGNAL(triggered()), this, SLOT(showWindowConfigurationTriggered()));
    QObject::connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    QSystemTrayIcon::show();
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

    setContextMenu(systemTrayMenu);
}

void SystemTrayIcon::takeSelectedAreaScreenTriggered()
{
    fileName = getNewFileName(".png");
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
    QString fileName = getNewFileName(".png");
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
    if(settings.value(playSoundSettingName).toBool())
        fileSendedSound.play();

    const QString urlPath = getUploadedFileURL(fileName);

    if(settings.value(copyToClipboardSettingName).toBool())
        QApplication::clipboard()->setText(urlPath);

    if(settings.value(showNotificationsSettingName).toBool())
        this->showMessage(applicationName, tr("UPLOAD_SUCCESS_WITH_URL", "Congratulation !\nUpload success. The URL is :\n") + urlPath);
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
    configurationWindows->show();
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
}

SystemTrayIcon::~SystemTrayIcon()
{
    delete configurationWindows;
}
