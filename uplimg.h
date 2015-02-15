#ifndef UPLIMG_H
#define UPLIMG_H

#include <QObject>
#include <QPixmap>
#include <QColor>

#include "core/systemtrayicon.h"
#include "core/screentaker.h"
#include "file/filemanager.h"
#include "network/filesender.h"
#include "windows/mainwindow.h"

#include <iostream>

/* This link all modules between them */

class Uplimg : public QObject
{
    Q_OBJECT
public:
    explicit Uplimg(QObject *parent = 0);
    ~Uplimg();
    void start();

    SystemTrayIcon *getSystemTray();

private:
    void initModules();
    void linkConnections();

    SystemTrayIcon * systemTray;
    ScreenTaker * screenTaker;
    FileManager * fileManager;
    FileSender * fileSender;
    MainWindow * mainWindow;


signals:

public slots:
    void startCaptureFullScreenProccess();

    void startCaptureSelectedScreenProccess();
    void captureSelectedScreenProccessCanceled();
};

#endif // UPLIMG_H
