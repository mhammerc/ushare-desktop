#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlComponent>

class MainWindow : public QObject
{
    Q_OBJECT
public:
    explicit MainWindow(QObject *parent = 0);
    ~MainWindow();

private:
    QQmlEngine engine;
    QQmlComponent  * component;
    QObject * window;

signals:

public slots:
    void show();
    void hide();
};

#endif // MAINWINDOW_H
