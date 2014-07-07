#pragma once
#ifndef SHARED_H
#define SHARED_H

#include <QApplication>
#include <QString>
#include <QSettings>
#include <iostream>

namespace Uplimg
{

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

}
#endif // SHARED_H
