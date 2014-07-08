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

#include <iostream>

#include "ftpconfiguration.h"
#include "httpconfiguration.h"

class SystemTrayIcon;

class ConfigurationWindows : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigurationWindows(SystemTrayIcon * parent, QWidget *qwidget = 0);
    ~ConfigurationWindows();

protected:
    SystemTrayIcon * parent;
    const QString windowTitle;
    QSettings settings;

    /* Settings name */
    const QString runOnStartupSettingName;
    const QString showNotificationsSettingName;
    const QString playSoundSettingName;
    const QString copyToClipboardSettingName;
    const QString langSettingName;
    const QString FTPMethodSettingName;
    const QString choosedMethodSettingName;
    const QString autoOpenToBrowserSettingName;
    const QString imageTypeSettingName;
    const QString imageQualitySettingName;
    const QString localSaveSettingName;
    const QString localSavePathSettingName;
    const QString localMethodSettingName;

    QVBoxLayout * mainLayout;
    QTabWidget * windowContent;

    /* General */
    QWidget * generalSection;
    QVBoxLayout * generalLayout;

    //General settings
    QGroupBox * generalSettings;
    QFormLayout * generalFormLayout;
    QCheckBox * runOnStartup;
    QComboBox * lang;
    QSlider * imageQuality;
    QLabel * imageQualityShower;
    QHBoxLayout * localSaveLayout;
    QCheckBox * localSave;
    QLineEdit * localSavePath;
    QPushButton * localSavePathChooser;

    //On successfull upload settings
    QGroupBox * onSuccessSettings;
    QFormLayout * onSuccessFormLayout;
    QCheckBox * playSound;
    QCheckBox * showNotifications;
    QCheckBox * copyToClipboard;
    QCheckBox * autoOpenToBrowser;
    QComboBox * imageType;
    QHBoxLayout * imageQualityLayout;

    QHBoxLayout * validateGeneralLayout;
    QPushButton * validateGeneral;


    /* Online Services */
    QWidget * uploadSection;
    QVBoxLayout * uploadLayout;
    QGroupBox * onlineServices;
    QVBoxLayout * onlineServicesLayout;

    QHBoxLayout * localMethodLayout;
    QRadioButton * localMethod;
    QLineEdit * localMethodPath;
    QPushButton * localMethodPathChooser;

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

    QHBoxLayout * validateUploadLayout;
    QPushButton * validateUpload;

    /* HotKeys */
    QWidget * hotkeysSection;
    QVBoxLayout * hotkeysLayout;
    QHBoxLayout * validateHotkeysLayout;
    QPushButton * validateHotkeys;

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

    QHBoxLayout * validateCreditLayout;
    QPushButton * validateCredit;

    //Fonctions
    void setUpUI();
    void setUpGeneralSectionUI();
    void setUpUploadSectionUI();
    void setUpHotkeysSectionUI();
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
    void localMethodPathSettingsModified(QString);
    void localMethodPathSettingsClicked();
    void imageTypeSettingModified(QString);
    void imageQualitySettingModified(int);
    void FTPMethodSettingModified(bool);
    void HTTPMethodSettingModified(bool);

    void configureFTP();
    void configureHTTP();


};

#endif // CONFIGURATIONWINDOWS_H
