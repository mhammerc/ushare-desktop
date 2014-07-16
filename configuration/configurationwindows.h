#ifndef CONFIGURATIONWINDOWS_H
#define CONFIGURATIONWINDOWS_H

#include <QApplication>
#include <QWidget>
#include <QTabWidget>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QCheckBox>
#include <QComboBox>
#include <QSettings>
#include <QGroupBox>
#include <QRadioButton>
#include <QPushButton>
#include <QCloseEvent>
#include <QTranslator>
#include <QLabel>
#include <QSizePolicy>
#include <QTextEdit>
#include <QListWidget>
#include <QListWidgetItem>
#include <QMessageBox>
#include <QShortcut>
#include <QFileDialog>
#include <QLocale>
#include <QColorDialog>
#include <QTableView>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include <iostream>

#include "ftpconfiguration.h"
#include "httpconfiguration.h"
#include "shortcutgetter.h"
#include "shared.h"

class SystemTrayIcon;

class ConfigurationWindows : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigurationWindows(SystemTrayIcon * parent, QWidget *qwidget = 0);
    ~ConfigurationWindows();

protected:
    virtual void hideEvent(QHideEvent *);

    SystemTrayIcon * parent;
    const QString windowTitle;
    QSettings settings;

    QVBoxLayout * mainLayout;
    QTabWidget * windowContent;

    /* General */
    QWidget * generalSection;
    QVBoxLayout * generalLayout;

    //General settings
    QGroupBox * generalSettings;
    QFormLayout * generalFormLayout;
#ifdef _WIN32
    QCheckBox * runOnStartup;
#endif
    QComboBox * lang;
    QHBoxLayout * selectingAreaColorLayout;
    QColor selectingAreaColor;
    QLabel * selectingAreaColorShower;
    QPushButton * selectingAreaColorOpener;
    QCheckBox * selectingAreaColorRandomize;

    //On successfull upload settings
    QGroupBox * onSuccessSettings;
    QFormLayout * onSuccessFormLayout;
    QCheckBox * playSound;
    QCheckBox * showNotifications;
    QCheckBox * copyToClipboard;
    QCheckBox * autoOpenToBrowser;

    /* Online Services */
    QWidget * uploadSection;
    QVBoxLayout * uploadLayout;
    QGroupBox * onlineServices;
    QVBoxLayout * onlineServicesLayout;

    QRadioButton * uplimgWeb;

    QRadioButton * localMethod;

    QRadioButton * FTPMethod;
    QPushButton * configureFTPButton;
    QHBoxLayout * FTPLayout;
    FTPConfiguration * FTPConf;

    QRadioButton * HTTPMethod;
    QLabel * HTTPWarning;
    QPushButton * configureHTTPButton;
    QHBoxLayout * HTTPLayoutForRadioAndPushButton;
    QVBoxLayout * HTTPLayout;
    HTTPConfiguration * HTTPConf;

    QFormLayout * pictureLayout;
    QGroupBox * picture;
    QComboBox * imageType;
    QHBoxLayout * imageQualityLayout;
    QSlider * imageQuality;
    QLabel * imageQualityShower;
    QHBoxLayout * localSaveLayout;
    QCheckBox * localSave;
    QLineEdit * localSavePath;
    QPushButton * localSavePathChooser;

    /* HotKeys */
    QWidget * hotkeysSection;
    QVBoxLayout * hotkeysLayout;
    QGroupBox * hotkeysGroupBox;
    QGroupBox * hotkeysIntermediateGroupBox;
    QVBoxLayout * hotkeysBindingLayout;
    QLabel * hotkeysWelcomeText;
    QFormLayout * hotkeysFormLayout;
    ShortcutGetter * takeFullScreenShortcut;
    ShortcutGetter * takeSelectedScreenShortcut;
    ShortcutGetter * uploadFileShortcut;
    ShortcutGetter * uploadClipboardShortcut;
    QLabel * warningHotkeysDisabled;

    /* Update */
    QWidget * updateSection;
    QVBoxLayout * updateMainLayout;
    QGroupBox * updateGroupBox;
    QHBoxLayout * updateLayout;
    QFormLayout * updateVersionLayout;
    QLabel * lastVersion;
    QUrl updateLink;
    QVBoxLayout * updateButtonLayout;
    QPushButton * verifyUpdatePushButton;
    QPushButton * updatePushButton;

    QNetworkAccessManager * updateManager;

    /* Credits */
    QWidget * creditSection;
    QVBoxLayout * creditLayout;
    //Header
    QLabel * openSourceText;
    //Made with
    QHBoxLayout * madeWithLayout;
    QPushButton * madeWithSFML;
    QPushButton * madeWithQt;
    QPushButton * madeWithQxt;
    QTextEdit * SFMLLicence;
    QTextEdit * LGPLLicence;
    //Contributors
    QLabel * leadDevelopper;
    QHBoxLayout * allContributorsLayout;
    QListWidget * allContributorsOne;
    QListWidget * allContributorsTwo;
    QLabel * happy4Ever;

    QHBoxLayout * validateLayout;
    QLabel * version;
    QPushButton * validate;

    //Fonctions
    void setUpUI();
    void setUpGeneralSectionUI();
    void setUpUploadSectionUI();
    void setUpHotkeysSectionUI();
    void setUpUpdateSectionUI();
    void setUpCreditsSectionUI();

    virtual void closeEvent(QCloseEvent *event);
    virtual void keyPressEvent(QKeyEvent *);

signals:
    void easterEgg();

public slots :
    void runOnStartupSettingModified(bool);
    void autoOpenToBrowserSettingModified(bool);
    void showNotificationSettingModified(bool);
    void playSoundSettingModified(bool);
    void copyToClipboardSettingModified(bool);
    void langSettingModified(QString);
    void localSaveSettingsModified(bool);
    void localSavePathSettingsModified(QString);
    void localSavePathSettingsClicked();
    void localMethodSettingsModified(bool);
    void imageTypeSettingModified(QString);
    void imageQualitySettingModified(int);
    void uplimgWebMethodSettingModified(bool);
    void FTPMethodSettingModified(bool);
    void HTTPMethodSettingModified(bool);
    void selectingAreaColorClicked();
    void selectingAreaColorRandomizer(bool);
    void currentTabChanged(int);
    void resetTab();

    void takeFullScreenShortcutChanged(QString);
    void takeSelectedAreaScreenShortcutChanged(QString);
    void uploadFileShortcutChanged(QString);
    void uploadClipboardShortcutChanged(QString);

    void verifyUpdate();
    void verifyUpdateFinished(QNetworkReply*);
    void downloadUpdate();


    void configureFTP();
    void configureHTTP();


};

#endif // CONFIGURATIONWINDOWS_H
