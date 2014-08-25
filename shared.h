#ifndef SHARED_H
#define SHARED_H

#include <QApplication>
#include <QObject>
#include <QString>
#include <QSettings>
#include <QStandardPaths>
#include <QTime>
#include <QUrl>
#include <QDesktopServices>
#include <QClipboard>

#include "widgets/label.h"
#include "widgets/button.h"
#include "widgets/topbar.h"
#include "widgets/checkbox.h"
#include "widgets/radiobutton.h"
#include "widgets/slider.h"
#include "widgets/combobox.h"
#include "widgets/listwidget.h"
#include "widgets/groupbox.h"
#include "widgets/tabwidget.h"
#include "widgets/lineedit.h"

#include "notificationwindow.h"

#include "containers/file.h"

/* Contain all registry access */
namespace Reg
{
QString const autoOpenToBrowser("configuration/autoOpenToBrowser");
QString const blueArea("configuration/color/selectAreaScreen/blue");
QString const choosedMethod("configuration/method");
QString const copyToClipboard("configuration/clipboard");
QString const FTPBasePath("configuration/ftp/basePath");
QString const FTPHost("configuration/ftp/host");
QString const FTPPassword("configuration/ftp/password");
QString const FTPPort("configuration/ftp/port");
QString const FTPUsername("configuration/ftp/username");
QString const FTPWebPath("configuration/ftp/webPath");
QString const greenArea("configuration/color/selectAreaScreen/green");
QString const HTTPFileFieldName("configuration/http/fieldName");
QString const HTTPHost("configuration/http/host");
QString const HTTPLinkFrom("configuration/http/linkFrom");
QString const HTTPPort("configuration/http/port");
QString const HTTPWebPath("configuration/http/webPath");
QString const imageFormat("configuration/imageType");
QString const imageQuality("configuration/imageQuality");
QString const lang("configuration/lang");
QString const linkFrom("configuration/http/linkFrom");
QString const localSave("configuration/localSave");
QString const localSavePath("configuration/localSavePath");
QString const playSound("configuration/playSound");
QString const randomizeArea("configuration/color/selectAreaScreen/randomize");
QString const redArea("configuration/color/selectAreaScreen/red");
QString const runOnStartup("configuration/runOnStartup");
QString const showNotifications("configuration/showNotifications");
QString const takeFullScrenShortcut("configuration/shortcut/takeFullScreen");
QString const takeSelectedAreaScreenShortcut("configuration/shortcut/takeSelectedArea");
QString const sendPasteShortcut("configuration/shortcut/sendPaste");
QString const uploadClipboardShortcut("configuration/shortcut/uploadClipboard");
QString const uploadFileShortcut("configuration/shortcut/uploadFile");
}

class var
{
public:
    static QUrl lastUrl;
};

namespace UplimgWeb
{
int const port(9375);
QString const host("http://insert.uplmg.com/upload.php");
QString const fileFieldName("uplimgFile");
}

namespace Uplimg
{
QString const applicationName("Uplimg");
QString const versionText("0.12 -> Alpha testing | leaks unautorized without express authorization");
QString const version("0.12");
QString const updateVersionLink("http://update.uplmg.com/latest.html");

enum HTTP_ACCESS_FILE_LINK { FROM_RESPONSE /* From HTTP response */, FROM_FIXED_LINK /* Web path */}; //From what link return the user on successfull HTTP upload : from HTTP response or from fixed choosed link

enum ImageFormat { JPEG, PNG, INVALID_FORMAT };

enum ErrorList { UPLOAD_FAIL, UPLOAD_METHOD_NOT_CHOOSED };

enum UploadMethod
{
    FTP,
    SSH,
    HTTP,
    UPLIMG_WEB,
    LOCAL,
    U_ERROR
};

enum FTPStatus
{
    FTP_SUCCESS,
    FTP_UNKNOWN_ERROR,
    FTP_CANT_CONNECT,
    FTP_CANT_LOGIN,
    FTP_CANT_PUT_FILE,
    FTP_SENDING,
    FTP_CONNECTING,
    FTP_CONNECTED,
    FTP_WAITING
};

class Utils : public QObject
{
    Q_OBJECT
public:
    Utils();

public slots:
    static Uplimg::ImageFormat getImageFormat()
    {
        QSettings settings;

        if(settings.value(Reg::imageFormat).toString() == "PNG")
            return Uplimg::ImageFormat::PNG;
        else if(settings.value(Reg::imageFormat).toString() == "JPEG")
            return Uplimg::ImageFormat::JPEG;
        else
            return Uplimg::ImageFormat::INVALID_FORMAT;
    }

    static Uplimg::UploadMethod getUploadMethod()
    {
        QSettings settings;

        if (settings.value(Reg::choosedMethod).toString().toStdString() == "FTP")
            return Uplimg::UploadMethod::FTP;
        else if (settings.value(Reg::choosedMethod).toString().toStdString() == "HTTP")
            return Uplimg::UploadMethod::HTTP;
        else if(settings.value(Reg::choosedMethod).toString().toStdString() == "UPLIMG_WEB")
            return Uplimg::UploadMethod::UPLIMG_WEB;
        else if (settings.value(Reg::choosedMethod).toString().toStdString() == "LOCAL")
            return Uplimg::UploadMethod::LOCAL;
        else
            return Uplimg::UploadMethod::U_ERROR;
    }

    static bool isValidURL(const std::string url)
    {
        if(url[0] == 'h')
            if(url[1] == 't' && url[2] == 't')
                if(url[3] == 'p')
                    if(url[4] == ':')
                        if(url[5] == '/' && url[6] == '/')
                            return true;
        return false;
    }

    static int getImageQuality()
    {
        QSettings settings;
        return settings.value(Reg::imageQuality).toInt();
    }

    static QString getNewFileName(Uplimg::ImageFormat ending)
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


    static QString getNewFileName(QString ending)
    {
        QTime time = QTime::currentTime();
        QDate date = QDate::currentDate();

        return QString::number(date.dayOfYear())
               + QString::number(time.hour())
               + QString::number(time.minute())
               + QString::number(time.second())
               + ending;
    }

    static QString getFileTempPath(const QString &screenName)
    {
        QSettings settings;

        if(settings.value(Reg::localSave).toBool() || settings.value(Reg::choosedMethod).toString() == "LOCAL")
            return settings.value(Reg::localSavePath).toString() + "/" + screenName;
        else
            return QStandardPaths::writableLocation(QStandardPaths::TempLocation)
                   + "/"
                   + screenName;
    }

    static QString getUploadedFileURL(const QString &fileName)
    {
        QSettings settings;

        if(Uplimg::Utils::getUploadMethod()  == Uplimg::UploadMethod::FTP)
            return settings.value(Reg::FTPWebPath, "http://").toString() + fileName;
        else if(Uplimg::Utils::getUploadMethod()  == Uplimg::UploadMethod::HTTP)
            return settings.value(Reg::HTTPWebPath, "http://").toString() + fileName;
        else
            return "error";
    }

    static void openLastUrl()
    {
        if(!var::lastUrl.toString().isNull())
            QDesktopServices::openUrl(var::lastUrl);
    }

    static void copyLastUrlToClipboard()
    {
        QApplication::clipboard()->setText(var::lastUrl.toString());
    }
};
}
#endif // SHARED_H
