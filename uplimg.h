#ifndef UPLIMG_H
#define UPLIMG_H

#include <QObject>

#include "core/systemtrayicon.h"
#include "windows/mainwindow.h"

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
    MainWindow * mainWindow;


signals:

public slots:
};

#endif // UPLIMG_H
