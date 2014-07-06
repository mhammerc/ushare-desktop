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

    QVBoxLayout * mainLayout;
    QTabWidget * windowContent;

    /* General */
    QWidget * generalSection;
    QFormLayout * formGeneral;
    QVBoxLayout * generalLayout;
    //Main Form
    QVBoxLayout * generalSettingsLayout;
    QGroupBox * generalSettings;

    QCheckBox * playSound;
    QCheckBox * showNotifications;
    QCheckBox * copyToClipboard;
    QCheckBox * autoOpenToBrowser;
    QCheckBox * runOnStartup;
    QComboBox * lang;

    /* Online Services */
    QWidget * uploadSection;
    QVBoxLayout * uploadLayout;
    QGroupBox * onlineServices;
    QVBoxLayout * onlineServicesLayout;

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

    /* HotKeys */
    QWidget * hotkeysSection;

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

    /* To close window */
    QHBoxLayout * validateLayout;
    QPushButton * validate;


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
    void FTPMethodSettingModified(bool);
    void HTTPMethodSettingModified(bool);

    void configureFTP();
    void configureHTTP();


};

#endif // CONFIGURATIONWINDOWS_H
