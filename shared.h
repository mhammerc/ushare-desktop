#pragma once
#ifndef SHARED_H
#define SHARED_H

#include <QApplication>
#include <QString>
#include <QSettings>

/* Contain all registry access */
namespace Reg
{
QString const HTTPWebPath("configuration/http/webPath");
QString const FTPWebPath("configuration/ftp/webPath");
QString const runOnStartup("configuration/runOnStartup");
QString const choosedMethod("configuration/method");
QString const showNotifications("configuration/showNotifications");
QString const playSound("configuration/playSound");
QString const copyToClipboard("configuration/clipboard");
QString const takeFullScrenShortcut("configuration/shortcut/takeFullScreen");
QString const takeSelectedAreaScreenShortcut("configuration/shortcut/takeSelectedArea");
QString const uploadFileShortcut("configuration/shortcut/uploadFile");
QString const uploadClipboardShortcut("configuration/shortcut/uploadClipboard");
QString const autoOpenToBrowser("configuration/autoOpenToBrowser");
QString const imageFormat("configuration/imageType");
QString const imageQuality("configuration/imageQuality");
QString const localSave("configuration/localSave");
QString const localSavePath("configuration/localSavePath");
QString const linkFrom("configuration/http/linkFrom");
QString const redArea("configuration/color/selectAreaScreen/red");
QString const greenArea("configuration/color/selectAreaScreen/green");
QString const blueArea("configuration/color/selectAreaScreen/blue");
QString const lang("configuration/lang");
QString const FTPHost("configuration/ftp/host");
QString const FTPPort("configuration/ftp/port");
QString const FTPUsername("configuration/ftp/username");
QString const FTPPassword("configuration/ftp/password");
QString const FTPBasePath("configuration/ftp/basePath");
QString const HTTPHost("configuration/http/host");
QString const HTTPPort("configuration/http/port");
QString const HTTPFileFieldName("configuration/http/fieldName");
QString const HTTPLinkFrom("configuration/http/linkFrom");
}

namespace Uplimg
{
QString const applicationName("Uplimg");

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
    ERROR
};

class Utils
{
public:
    Utils();

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
        else if (settings.value(Reg::choosedMethod).toString().toStdString() == "LOCAL")
            return Uplimg::UploadMethod::LOCAL;
        else
            return Uplimg::UploadMethod::ERROR;
    }

    static int getImageQuality()
    {
        QSettings settings;
        return settings.value(Reg::imageQuality).toInt();
    }
};
}
#endif // SHARED_H
