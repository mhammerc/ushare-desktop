#pragma once
#ifndef SHARED_H
#define SHARED_H

#include <QApplication>
#include <QString>
#include <QSettings>
#include <iostream>

namespace Uplimg
{

enum ImageFormat { JPEG, PNG, INVALID_FORMAT };

enum ErrorList { UPLOAD_FAIL, UPLOAD_METHOD_NOT_CHOOSED };

enum UploadMethod
{
    FTP,
    SSH,
    HTTP,
    UPLIMG_WEB,
    ERROR
};

}
#endif // SHARED_H
