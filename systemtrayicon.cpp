#include "systemtrayicon.h"

SystemTrayIcon::SystemTrayIcon(QObject *qobject) :
    QSystemTrayIcon(qobject)
{

    if(settings.value(Reg::runOnStartup).isNull()) //First time the application is started
        firstStart();

    configurationWindow = 0;
    lastUploadedFileSeparatorInserted = false;
    lastUploadedFileCounter = 0;

    setIcon(QIcon(":/icon/waiting.png"));
    setToolTip(tr("DAEMON_RUNNING"));

    iconTimer = new QTimer(this);
    iconTimer->setSingleShot(true);
    iconTimer->setInterval(3000);
    QObject::connect(iconTimer, SIGNAL(timeout()), this, SLOT(setWaitingIcon()));

    screenManager = new ScreenManager(this);
    fileSendedSound = new QSound(":/fileSended.wav", this);

    takeFullScreenKeySequence = QKeySequence(settings.value(Reg::takeFullScrenShortcut).toString());
    takeSelectedAreaKeySequence = QKeySequence(settings.value(Reg::takeSelectedAreaScreenShortcut).toString());
    uploadFileKeySequence = QKeySequence(settings.value(Reg::uploadFileShortcut).toString());
    uploadClipboardKeySequence = QKeySequence(settings.value(Reg::uploadClipboardShortcut).toString());

    takeFullScreenShortcut = new QxtGlobalShortcut(takeFullScreenKeySequence, this);
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

    QObject::connect(takeFullScreenShortcut, SIGNAL(activated()), this, SLOT(takeFullScrenTriggered()));
    QObject::connect(takeSelectedAreaScreenShortcut, SIGNAL(activated()), this, SLOT(takeSelectedAreaScreenTriggered()));
    QObject::connect(uploadFileShortcut, SIGNAL(activated()), this, SLOT(uploadSelectedFileTriggered()));
    QObject::connect(uploadClipboardShortcut, SIGNAL(activated()), this, SLOT(uploadClipboardTriggered()));
}

void SystemTrayIcon::setUpContextMenu()
{
    systemTrayMenu = new QMenu;

    takeScreen = systemTrayMenu->addAction(QIcon(":/contextMenu/icon/fullscreen.png"), tr("TAKE_NEW_FULLSCREEN"));
    takeSelectedScreen = systemTrayMenu->addAction(QIcon(":/contextMenu/icon/selectedScreen.png"), tr("TAKE_NEW_AREA_SELECTED_SCREEN"));
    uploadFile = systemTrayMenu->addAction(QIcon(":/contextMenu/icon/file.png"), tr("UPLOAD_CHOOSED_FILE"));
    uploadClipboard = systemTrayMenu->addAction(QIcon(":/contextMenu/icon/clipboard.png"), tr("UPLOAD_CLIPBOARD"));
    systemTrayMenu->addSeparator();
    showConfiguration = systemTrayMenu->addAction(tr("CONFIGURATION", "In system tray icon"));
    quit = systemTrayMenu->addAction(tr("EXIT"));

    takeScreen->setShortcut(takeFullScreenShortcut->shortcut());
    takeSelectedScreen->setShortcut(takeSelectedAreaScreenShortcut->shortcut());
    uploadFile->setShortcut(uploadFileShortcut->shortcut());
    uploadClipboard->setShortcut(uploadClipboardShortcut->shortcut());

    systemTrayMenu->setTearOffEnabled(true);

    setContextMenu(systemTrayMenu);
}

void SystemTrayIcon::takeSelectedAreaScreenTriggered()
{
    fileName = getNewFileName(Uplimg::Utils::getImageFormat());
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
    QString fileName = getNewFileName(Uplimg::Utils::getImageFormat());
    QString pathToFile = getFileTempPath(fileName);

    if (screenManager->autoSendFile(screenManager->captureFullScreen(pathToFile)))
        fileSended(fileName);
    else
        throwErrorAlert(Uplimg::ErrorList::UPLOAD_FAIL);
}

void SystemTrayIcon::uploadSelectedFileTriggered()
{
    QString path = QFileDialog::getOpenFileName(0, tr("SELECT_FILE"));

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
    setIcon(QIcon(":/icon/success.png"));
    iconTimer->start();

    if(Uplimg::Utils::getUploadMethod() != Uplimg::UploadMethod::LOCAL && Uplimg::Utils::getUploadMethod() != Uplimg::UploadMethod::ERROR)
        {
            if(settings.value(Reg::playSound).toBool())
                fileSendedSound->play();

            if(settings.value(Reg::linkFrom).toString() != "FROM_HTTP" || Uplimg::Utils::getUploadMethod() != Uplimg::UploadMethod::HTTP)
                {
                    const QString urlPath = getUploadedFileURL(fileName);
                    lastUrl.setUrl(urlPath);
                }

            addUploadedFileInContextMenu();

            if(settings.value(Reg::autoOpenToBrowser).toBool())
                openLastUrl();

            if(settings.value(Reg::copyToClipboard).toBool())
                copyLastUrlToClipboard();

            if(settings.value(Reg::showNotifications).toBool())
                this->showMessage(Uplimg::applicationName, tr("UPLOAD_SUCCESS_WITH_URL", "Congratulation !\nUpload success. The URL is :\n") + lastUrl.toString());
        }
    else if(Uplimg::Utils::getUploadMethod()  == Uplimg::UploadMethod::LOCAL)
        {
            if(settings.value(Reg::playSound).toBool())
                fileSendedSound->play();

            if(settings.value(Reg::showNotifications).toBool())
                this->showMessage(Uplimg::applicationName, tr("UPLOAD_SUCCESS_LOCAL"));
        }
}

void SystemTrayIcon::addUploadedFileInContextMenu()
{
    if(!lastUploadedFileSeparatorInserted)
    {
        lastUploadedFileSeparator = systemTrayMenu->insertSeparator(systemTrayMenu->actions().at(0));
        lastUploadedFileSeparatorInserted = true;
    }

    QMenu * pictureMenu = new QMenu(lastUrl.fileName());
    QAction * openToBrowser = pictureMenu->addAction(tr("OPEN_TO_BROWSER"));
    QAction * copyToClipboard = pictureMenu->addAction(tr("COPY_TO_CLIPBOARD"));
    systemTrayMenu->insertMenu(lastUploadedFileSeparator, pictureMenu);

    QObject::connect(pictureMenu->menuAction(), SIGNAL(toggled(bool)), this, SLOT(openLastUrl())); //Don't work
    QObject::connect(openToBrowser, SIGNAL(triggered()), this, SLOT(openLastUrl()));
    QObject::connect(copyToClipboard, SIGNAL(triggered()), this, SLOT(copyLastUrlToClipboard()));

    if(lastUploadedFileCounter == 5)
    {
        QAction * lastAction = systemTrayMenu->actions().at(0);
        systemTrayMenu->removeAction(lastAction);
    }
    else
        ++lastUploadedFileCounter;
}

void SystemTrayIcon::copyLastUrlToClipboard()
{
    QApplication::clipboard()->setText(lastUrl.toString());
}

void SystemTrayIcon::setWaitingIcon()
{
    setIcon(QIcon(":/icon/waiting.png"));
}

void SystemTrayIcon::uploadClipboardTriggered()
{
    /* ONLY SUPPORTED FOR WINDOWS, NEVER TESTED ON X11 OR MAC */
    /* IF CLIPBOARD POINT TO FILE, WE UPLOAD IT INSTEAD FILE PATH */
    QString clipboard = QApplication::clipboard()->text();
    clipboard = clipboard.right(clipboard.size()-8); //Windows automatically put file:/// at begin

    if(QFile::exists(clipboard)) //Clipboard is pointing to file
    {
        if(screenManager->autoSendFile(clipboard))
        {
            QFileInfo fi(clipboard);
            fileSended(fi.fileName());
        }
        return;
    }
    /* WINDOWS ONLY END */

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
    if(settings.value(Reg::localSave).toBool() || settings.value(Reg::choosedMethod).toString() == "LOCAL")
        return settings.value(Reg::localSavePath).toString() + "/" + screenName;
    else
        return QStandardPaths::writableLocation(QStandardPaths::TempLocation)
               + "/"
               + screenName;
}

QString SystemTrayIcon::getUploadedFileURL(const QString &fileName)
{
    if(Uplimg::Utils::getUploadMethod()  == Uplimg::UploadMethod::FTP)
        return settings.value(Reg::FTPWebPath, "http://").toString() + fileName;
    else if(Uplimg::Utils::getUploadMethod()  == Uplimg::UploadMethod::HTTP)
        return settings.value(Reg::HTTPWebPath, "http://").toString() + fileName;
    else
        return "error";
}

void SystemTrayIcon::showWindowConfigurationTriggered()
{
    if(configurationWindow == 0)
        configurationWindow = new ConfigurationWindows(this);
    configurationWindow->show();
    configurationWindow->setWindowState(Qt::WindowActive);
}

void SystemTrayIcon::throwErrorAlert(const QString &text)
{
    QMessageBox::critical(0, "Uplimg", text);
}

void SystemTrayIcon::throwErrorAlert(const Uplimg::ErrorList &error)
{
    setIcon(QIcon(":/icon/error.png"));
    iconTimer->start();

    if (error == Uplimg::ErrorList::UPLOAD_FAIL)
        {
            const QString text(tr("UPLOAD_FAILED"));
            this->showMessage(Uplimg::applicationName, text);
        }
    else if(error == Uplimg::ErrorList::UPLOAD_METHOD_NOT_CHOOSED)
        {
            const QString text(tr("NO_METHOD_TO_UPLOAD_CHOOSED"));
            this->showMessage(Uplimg::applicationName, text);
        }
}

void SystemTrayIcon::firstStart()
{
    settings.setValue(Reg::runOnStartup, true);
    settings.setValue(Reg::showNotifications, true);
    settings.setValue(Reg::playSound, true);
    settings.setValue(Reg::copyToClipboard, true);
    settings.setValue(Reg::autoOpenToBrowser, false);
    settings.setValue(Reg::localSave, false);
    settings.setValue(Reg::choosedMethod, "FTP");
    settings.setValue(Reg::takeFullScrenShortcut, "Alt+1");
    settings.setValue(Reg::takeSelectedAreaScreenShortcut, "Alt+2");
    settings.setValue(Reg::uploadFileShortcut, "Alt+3");
    settings.setValue(Reg::uploadClipboardShortcut, "Alt+4");
    settings.setValue(Reg::imageFormat, "JPEG");
    settings.setValue(Reg::imageQuality, 100);
    settings.setValue(Reg::localSavePath, QStandardPaths::standardLocations(QStandardPaths::PicturesLocation));
    settings.setValue(Reg::redArea, 10);
    settings.setValue(Reg::greenArea, 210);
    settings.setValue(Reg::blueArea, 10);
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

SystemTrayIcon::~SystemTrayIcon()
{
    configurationWindow->deleteLater();
}
