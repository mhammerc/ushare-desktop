#include "mainwindow.h"

MainWindow::MainWindow(QObject *parent) : QObject(parent)
{
    component = new QQmlComponent(&engine, QUrl::fromLocalFile("/home/imote/Development/Uplimg/qml/mainWindow.qml"), this);
    window = component->create();
}

MainWindow::~MainWindow()
{

}

void MainWindow::show()
{
    window->setProperty("visible", true);
}

void MainWindow::hide()
{
    window->setProperty("visible", false);
}

