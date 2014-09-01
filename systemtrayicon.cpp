/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#include "systemtrayicon.h"

SystemTrayIcon::SystemTrayIcon(QObject *qobject) :
    QSystemTrayIcon(qobject), fileSendedSound(this)
{
    if(settings.value(Reg::runOnStartup).isNull()) //First time the application is started
        firstStart();

    configurationWindow = 0;
    lastUploadedFileSeparatorInserted = false;
    lastUploadedFileCounter = 0;
    actionBeing = false;

    setIcon(QIcon(":/icon/waiting.png"));
    setToolTip(tr("DAEMON_RUNNING"));

    iconTimer = new QTimer(this);
    iconTimer->setSingleShot(true);
    iconTimer->setInterval(3000);
    QObject::connect(iconTimer, SIGNAL(timeout()), this, SLOT(setWaitingIcon()));

    screenManager = new FileManager(this);

    takeFullScreenKeySequence = QKeySequence(settings.value(Reg::takeFullScrenShortcut).toString());
    takeSelectedAreaKeySequence = QKeySequence(settings.value(Reg::takeSelectedAreaScreenShortcut).toString());
    sendPasteKeySequence = QKeySequence(settings.value(Reg::sendPasteShortcut).toString());
    uploadFileKeySequence = QKeySequence(settings.value(Reg::uploadFileShortcut).toString());
    uploadClipboardKeySequence = QKeySequence(settings.value(Reg::uploadClipboardShortcut).toString());

    takeFullScreenShortcut = new ShortcutManager(takeFullScreenKeySequence, this);
    takeSelectedAreaScreenShortcut = new ShortcutManager(takeSelectedAreaKeySequence, this);
    sendPasteShortcut = new ShortcutManager(sendPasteKeySequence, this);
    uploadFileShortcut = new ShortcutManager(uploadFileKeySequence, this);
    uploadClipboardShortcut = new ShortcutManager(uploadClipboardKeySequence, this);

    setUpContextMenu();

    QObject::connect(takeScreen, SIGNAL(triggered()), this, SLOT(takeFullScrenTriggered()));
    QObject::connect(takeSelectedScreen, SIGNAL(triggered()), this, SLOT(takeSelectedAreaScreenTriggered()));
    QObject::connect(sendPaste, SIGNAL(triggered()), this, SLOT(sendPasteTriggered()));
    QObject::connect(uploadFile, SIGNAL(triggered()), this, SLOT(uploadSelectedFileTriggered()));
    QObject::connect(uploadClipboard, SIGNAL(triggered()), this, SLOT(uploadClipboardTriggered()));
    QObject::connect(showConfiguration, SIGNAL(triggered()), this, SLOT(showWindowConfigurationTriggered()));
    QObject::connect(quit, SIGNAL(triggered()), qApp, SLOT(quit()));

    QObject::connect(this, SIGNAL(messageClicked()), this, SLOT(openLastUrl()));
    QObject::connect(this, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));

    QObject::connect(takeFullScreenShortcut, SIGNAL(activated()), this, SLOT(takeFullScrenTriggered()));
    QObject::connect(takeSelectedAreaScreenShortcut, SIGNAL(activated()), this, SLOT(takeSelectedAreaScreenTriggered()));
    QObject::connect(sendPasteShortcut, SIGNAL(activated()), this, SLOT(sendPasteTriggered()));
    QObject::connect(uploadFileShortcut, SIGNAL(activated()), this, SLOT(uploadSelectedFileTriggered()));
    QObject::connect(uploadClipboardShortcut, SIGNAL(activated()), this, SLOT(uploadClipboardTriggered()));
}

void SystemTrayIcon::setUpContextMenu()
{
    systemTrayMenu = new QMenu;

    takeScreen = systemTrayMenu->addAction(QIcon(":/contextMenu/icon/fullscreen.png"), tr("TAKE_NEW_FULLSCREEN"));
    takeSelectedScreen = systemTrayMenu->addAction(QIcon(":/contextMenu/icon/selectedScreen.png"), tr("TAKE_NEW_AREA_SELECTED_SCREEN"));
    sendPaste = systemTrayMenu->addAction(tr("SEND_PASTE"));
    uploadFile = systemTrayMenu->addAction(QIcon(":/contextMenu/icon/file.png"), tr("UPLOAD_CHOOSED_FILE"));
    uploadClipboard = systemTrayMenu->addAction(QIcon(":/contextMenu/icon/clipboard.png"), tr("UPLOAD_CLIPBOARD"));
    systemTrayMenu->addSeparator();
    showConfiguration = systemTrayMenu->addAction(tr("CONFIGURATION", "In system tray icon"));
    quit = systemTrayMenu->addAction(tr("EXIT"));

    takeScreen->setShortcut(takeFullScreenShortcut->shortcut());
    takeSelectedScreen->setShortcut(takeSelectedAreaScreenShortcut->shortcut());
    sendPaste->setShortcut(sendPasteShortcut->shortcut());
    uploadFile->setShortcut(uploadFileShortcut->shortcut());
    uploadClipboard->setShortcut(uploadClipboardShortcut->shortcut());

    systemTrayMenu->setTearOffEnabled(true);

    setContextMenu(systemTrayMenu);
}

void SystemTrayIcon::takeSelectedAreaScreenTriggered()
{
    if(!actionBeing)
        {
            newActionStarted();
            fileInfo.realName = Uplimg::Utils::getNewFileName(Uplimg::Utils::getImageFormat());
            fileInfo.path = Uplimg::Utils::getFileTempPath(fileInfo.realName);
            fileInfo.type = "image";
            screenManager->captureSelectedZone(fileInfo);
        }
}

void SystemTrayIcon::sendPasteTriggered()
{
    screenManager->startPastMode();
}

void SystemTrayIcon::sendSelectedArea()
{
    screenManager->autoSendFile(fileInfo);
}

void SystemTrayIcon::takeFullScrenTriggered()
{
    if(!actionBeing)
        {
            newActionStarted();
            File file;
            file.realName = Uplimg::Utils::getNewFileName(Uplimg::Utils::getImageFormat());
            file.path = Uplimg::Utils::getFileTempPath(file.realName);

            screenManager->autoSendFile(screenManager->captureFullScreen(file));
        }
}

void SystemTrayIcon::uploadSelectedFileTriggered()
{
    if(!actionBeing)
        {
            newActionStarted();
            File file;
            file.path = QFileDialog::getOpenFileName(0, tr("SELECT_FILE"));
            file.type = "file";


            if(!file.path.isNull())
                {
                    QFileInfo fileInfo(file.path);
                    file.realName = fileInfo.fileName();
                    screenManager->autoSendFile(file);
                }
            else
            {
                lastActionFinished();
                setIcon(QIcon(":/icon/waiting.png"));
            }
        }
}

void SystemTrayIcon::fileSended(File const &file)
{
    lastActionFinished();
    setIcon(QIcon(":/icon/success.png"));
    iconTimer->start();

    if(Uplimg::Utils::getUploadMethod() == Uplimg::UploadMethod::UPLIMG_WEB || Uplimg::Utils::getUploadMethod() == Uplimg::UploadMethod::HTTP)
        {
            if(!Uplimg::Utils::isValidURL(var::lastUrl.toString().toStdString()))
                return throwErrorAlert(var::lastUrl.toString());

        }

    if(Uplimg::Utils::getUploadMethod() != Uplimg::UploadMethod::LOCAL && Uplimg::Utils::getUploadMethod() != Uplimg::UploadMethod::U_ERROR)
        {
            if(settings.value(Reg::playSound).toBool())
                fileSendedSound.play();

            if((settings.value(Reg::linkFrom).toString() != "FROM_HTTP" || Uplimg::Utils::getUploadMethod() != Uplimg::UploadMethod::HTTP) && Uplimg::Utils::getUploadMethod() != Uplimg::UploadMethod::UPLIMG_WEB)
                var::lastUrl.setUrl(Uplimg::Utils::getUploadedFileURL(file.realName));

            addUploadedFileInContextMenu();

            if(settings.value(Reg::autoOpenToBrowser).toBool())
                Uplimg::Utils::openLastUrl();

            if(settings.value(Reg::copyToClipboard).toBool())
                Uplimg::Utils::copyLastUrlToClipboard();

            if(settings.value(Reg::showNotifications).toBool())
                this->showNotification(Uplimg::applicationName, tr("UPLOAD_SUCCESS_WITH_URL") + var::lastUrl.toDisplayString());
        }
    else if(Uplimg::Utils::getUploadMethod()  == Uplimg::UploadMethod::LOCAL)
        {
            if(settings.value(Reg::playSound).toBool())
                fileSendedSound.play();

            if(settings.value(Reg::showNotifications).toBool())
                this->showNotification(Uplimg::applicationName, tr("UPLOAD_SUCCESS_LOCAL"));
        }
}

void SystemTrayIcon::lastActionFinished()
{
    actionBeing = false;
}

void SystemTrayIcon::newActionStarted()
{
    actionBeing = true;
    setIcon(QIcon(":/icon/uploading.png"));
}

void SystemTrayIcon::addUploadedFileInContextMenu()
{
    if(!lastUploadedFileSeparatorInserted)
        {
            lastUploadedFileSeparator = systemTrayMenu->insertSeparator(systemTrayMenu->actions().at(0));
            lastUploadedFileSeparatorInserted = true;
        }

    QMenu * pictureMenu = new QMenu(var::lastUrl.fileName());
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

void SystemTrayIcon::setWaitingIcon()
{
    setIcon(QIcon(":/icon/waiting.png"));
}

void SystemTrayIcon::uploadClipboardTriggered()
{
    if(!actionBeing)
        {
            newActionStarted();
            File file;
            /* ONLY SUPPORTED FOR WINDOWS, NEVER TESTED ON X11 OR MAC */
            /* IF CLIPBOARD POINT TO FILE, WE UPLOAD IT INSTEAD FILE PATH */
            file.path = QApplication::clipboard()->text();
            file.path = file.path.right(file.path.size()-8); //Windows automatically insert file:/// at begin
            file.type = "file";
            if(QFile::exists(file.path)) //Clipboard is pointing to file
                {
                    QFileInfo fi(file.path);
                    file.realName = fi.fileName();
                    screenManager->autoSendFile(file);
                    return;
                }
            /* WINDOWS ONLY END */

            file.type = "paste";
            file.realName = Uplimg::Utils::getNewFileName(".txt");
            file.path = Uplimg::Utils::getFileTempPath(file.realName);
            std::ofstream physicFile(file.path.toStdString().c_str());
            if (physicFile)
                {
                    physicFile << QApplication::clipboard()->text().toStdString();
                    physicFile.close();
                    screenManager->autoSendFile(file);
                }
        }
}

void SystemTrayIcon::showWindowConfigurationTriggered()
{
    if(configurationWindow == 0)
        {
            configurationWindow = new ConfigurationWindows(this);
        }
    configurationWindow->resetTab();
    configurationWindow->show();
}

void SystemTrayIcon::throwErrorAlert(const QString &text)
{
    lastActionFinished();
    QMessageBox::critical(0, "Uplimg", text);
}

void SystemTrayIcon::throwErrorAlert(const Uplimg::ErrorList error)
{
    setIcon(QIcon(":/icon/error.png"));
    iconTimer->start();
    lastActionFinished();

    if (error == Uplimg::ErrorList::UPLOAD_FAIL)
        {
            QString const text(tr("UPLOAD_FAILED"));
            this->showNotification(Uplimg::applicationName, text);
        }
    else if(error == Uplimg::ErrorList::UPLOAD_METHOD_NOT_CHOOSED)
        {
            QString const text(tr("NO_METHOD_TO_UPLOAD_CHOOSED"));
            this->showNotification(Uplimg::applicationName, text);
        }
    else if(error == Uplimg::ErrorList::CANT_SAVE_IMAGE_TEMP)
        {
            QString const text(tr("CANT_SAVE_IMAGE_TEMP"));
            this->showNotification(Uplimg::applicationName, text);
        }
}

void SystemTrayIcon::throwErrorAlert(Uplimg::FTPStatus const error)
{
    setIcon(QIcon(":/icon/error.png"));
    iconTimer->start();
    lastActionFinished();

    if(error == Uplimg::FTP_CANT_CONNECT)
        showNotification(Uplimg::applicationName, tr("FTP_CANT_CONNECT"));
    else if(error == Uplimg::FTP_CANT_LOGIN)
        showNotification(Uplimg::applicationName, tr("FTP_CANT_LOGIN"));
    else if(error == Uplimg::FTP_CANT_PUT_FILE)
        showNotification(Uplimg::applicationName, tr("FTP_CANT_PUT_FILE"));
}

void SystemTrayIcon::firstStart()
{
    settings.setValue(Reg::runOnStartup, false);
    settings.setValue(Reg::showNotifications, true);
    settings.setValue(Reg::playSound, true);
    settings.setValue(Reg::copyToClipboard, true);
    settings.setValue(Reg::autoOpenToBrowser, false);
    settings.setValue(Reg::localSave, false);
    settings.setValue(Reg::choosedMethod, "UPLIMG_WEB");
    settings.setValue(Reg::takeFullScrenShortcut, "Alt+1");
    settings.setValue(Reg::takeSelectedAreaScreenShortcut, "Alt+2");
    settings.setValue(Reg::sendPasteShortcut, "Alt+3");
    settings.setValue(Reg::uploadFileShortcut, "Alt+4");
    settings.setValue(Reg::uploadClipboardShortcut, "Alt+5");
    settings.setValue(Reg::imageFormat, "JPEG");
    settings.setValue(Reg::imageQuality, 100);
    settings.setValue(Reg::redArea, 10);
    settings.setValue(Reg::greenArea, 210);
    settings.setValue(Reg::blueArea, 10);
    settings.setValue(Reg::HTTPLinkFrom, "FROM_HTTP");
    QDir pictureDir(QStandardPaths::standardLocations(QStandardPaths::PicturesLocation).at(0));
    pictureDir.mkdir("Uplimg");
    pictureDir.cd("Uplimg");
    settings.setValue(Reg::localSavePath, pictureDir.absolutePath());
}

void SystemTrayIcon::disableHotkeys()
{
    takeFullScreenShortcut->setDisabled(true);
    takeSelectedAreaScreenShortcut->setDisabled(true);
    sendPasteShortcut->setDisabled(true);
    uploadFileShortcut->setDisabled(true);
    uploadClipboardShortcut->setDisabled(true);
}

void SystemTrayIcon::enableHotkeys()
{
    takeFullScreenShortcut->setEnabled(true);
    takeSelectedAreaScreenShortcut->setEnabled(true);
    sendPasteShortcut->setEnabled(true);
    uploadFileShortcut->setEnabled(true);
    uploadClipboardShortcut->setEnabled(true);
}

void SystemTrayIcon::enableEasterEgg()
{
    fileSendedSound.enableEasterEgg();
}

void SystemTrayIcon::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
    if(reason == QSystemTrayIcon::ActivationReason::Trigger)
        Uplimg::Utils::openLastUrl();
}

void SystemTrayIcon::takeFullScreenShortcutChanged(QString shortcut)
{
    takeFullScreenKeySequence = QKeySequence(shortcut);
    takeFullScreenShortcut->setShortcut(takeFullScreenKeySequence);
    takeScreen->setShortcut(takeFullScreenKeySequence);
}

void SystemTrayIcon::takeSelectedAreaScreenShortcutChanged(QString shortcut)
{
    sendPasteKeySequence = QKeySequence(shortcut);
    sendPasteShortcut->setShortcut(sendPasteKeySequence);
    sendPaste->setShortcut(sendPasteKeySequence);
}

void SystemTrayIcon::sendPasteShortcutChanged(QString shortcut)
{
    sendPasteKeySequence = QKeySequence(shortcut);
    sendPasteShortcut->setShortcut(sendPasteKeySequence);
    sendPaste->setShortcut(sendPasteKeySequence);
}

void SystemTrayIcon::uploadClipboardShortcutChanged(QString shortcut)
{
    uploadClipboardKeySequence = QKeySequence(shortcut);
    uploadClipboardShortcut->setShortcut(uploadClipboardKeySequence);
    uploadClipboard->setShortcut(uploadClipboardKeySequence);
}

void SystemTrayIcon::uploadFileShortcutChanged(QString shortcut)
{
    uploadFileKeySequence = QKeySequence(shortcut);
    uploadFileShortcut->setShortcut(uploadFileKeySequence);
    uploadFile->setShortcut(uploadFileKeySequence);
}

void SystemTrayIcon::openLastUrl()
{
    Uplimg::Utils::openLastUrl();
}

void SystemTrayIcon::copyLastUrlToClipboard()
{
    Uplimg::Utils::copyLastUrlToClipboard();
}

SystemTrayIcon::~SystemTrayIcon()
{
    configurationWindow->deleteLater();
}

void SystemTrayIcon::showNotification(const QString &title, const QString &message)
{
    new NotificationWindow(title, message, this, MESSAGE_TYPE::SUCCESS);
}
