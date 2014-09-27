/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

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
#include <QPainter>
#include <QGraphicsDropShadowEffect>

#include <iostream>

#include "ftpconfiguration.h"
#include "httpconfiguration.h"
#include "widgets/shortcutgetter.h"
#include "widgets/bottombar.h"
#include "shared.h"

class SystemTrayIcon;

class ConfigurationWindows : public QWidget
{
    Q_OBJECT
public:
    explicit ConfigurationWindows(SystemTrayIcon * parent, QWidget *qwidget = 0);
    ~ConfigurationWindows();
    void paintEvent(QPaintEvent *);

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

    //Top bar
    TopBarWidget * topBarWidget;

    //General settings
    QGroupBox * generalSettings;
    QFormLayout * generalFormLayout;
#ifdef _WIN32
    CheckBoxGreen * runOnStartup;
#endif
    QComboBox * lang;
    QHBoxLayout * selectingAreaColorLayout;
    QColor selectingAreaColor;
    LabelWithoutBackground * selectingAreaColorShower;
    ButtonBlue * selectingAreaColorOpener;
    CheckBoxGreen * selectingAreaColorRandomize;

    //On successfull upload settings
    QGroupBox * onSuccessSettings;
    QFormLayout * onSuccessFormLayout;
    CheckBoxGreen * playSound;
    CheckBoxGreen * showNotifications;
    CheckBoxGreen * copyToClipboard;
    CheckBoxGreen * autoOpenToBrowser;

    /* Online Services */
    QWidget * uploadSection;
    QVBoxLayout * uploadLayout;
    QGroupBox * onlineServices;
    QVBoxLayout * onlineServicesLayout;

    QHBoxLayout * uplimgWebLayout;
    QRadioButton * uplimgWeb;
    ButtonBlue * configureUplimgWeb;
    ButtonBlue * aboutUplimgWeb;

    QRadioButton * localMethod;

    QRadioButton * FTPMethod;
    ButtonBlue * configureFTPButton;
    QHBoxLayout * FTPLayout;
    FTPConfiguration * FTPConf;

    QRadioButton * HTTPMethod;
    LabelRed * HTTPWarning;
    ButtonBlue * configureHTTPButton;
    QHBoxLayout * HTTPLayoutForRadioAndPushButton;
    QVBoxLayout * HTTPLayout;
    HTTPConfiguration * HTTPConf;

    QFormLayout * pictureLayout;
    QGroupBox * picture;
    QComboBox * imageType;
    QHBoxLayout * imageQualityLayout;
    QSlider * imageQuality;
    LabelOrange * imageQualityShower;
    QHBoxLayout * localSaveLayout;
    CheckBoxGreen * localSave;
    QLineEdit * localSavePath;
    ButtonBlue * localSavePathChooser;

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
    ShortcutGetter * sendPasteShortcut;
    ShortcutGetter * uploadFileShortcut;
    ShortcutGetter * uploadClipboardShortcut;
    LabelOrange * warningHotkeysDisabled;

    /* Update */
    QWidget * updateSection;
    QVBoxLayout * updateMainLayout;
    QGroupBox * updateGroupBox;
    QHBoxLayout * updateLayout;
    QFormLayout * updateVersionLayout;
    QLabel * lastVersion;
    QUrl updateLink;
    QVBoxLayout * updateButtonLayout;
    ButtonBlue * verifyUpdatePushButton;
    ButtonBlue * updatePushButton;

    QNetworkAccessManager * updateManager;

    /* Credits */
    QWidget * creditSection;
    QVBoxLayout * creditLayout;
    QVBoxLayout * creditMainLayout;
    QGroupBox * creditGroupBox;
    //Header
    QLabel * openSourceText;
    //Made with
    QHBoxLayout * madeWithLayout;
    ButtonBlue * madeWithSFML;
    ButtonBlue * madeWithQt;
    ButtonBlue * uplimgLicenseButton;
    ButtonBlue * madeWithQxt;
    QTextEdit * uplimgLicense;
    QTextEdit * SFMLLicence;
    QTextEdit * LGPLLicence;
    //Contributors
    LabelOrange * leadDevelopper;
    LabelOrange * si0ls;
    QHBoxLayout * allContributorsLayout;
    QListWidget * allContributorsOne;
    QListWidget * allContributorsTwo;
    LabelBlue * happy4Ever;

    BottomBarConfigurationWindow * bottomBar;

    //Fonctions
    void setUpUI();
    void setUpTopBarUI();
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
    void sendPasteShortcutChanged(const QString &shortcut);
    void uploadFileShortcutChanged(QString);
    void uploadClipboardShortcutChanged(QString);

    void verifyUpdate();
    void verifyUpdateFinished(QNetworkReply*);
    void downloadUpdate();


    void configureFTP();
    void configureHTTP();

    void refreshCSS();
};

#endif // CONFIGURATIONWINDOWS_H
