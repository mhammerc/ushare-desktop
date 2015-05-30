#ifndef PASTEWINDOW_H
#define PASTEWINDOW_H

#include <QObject>
#include <QQmlEngine>
#include <QQmlComponent>
#include <QQuickItem>
#include <QQuickWindow>

class PasteWindow : public QObject
{
    Q_OBJECT
public:
    explicit PasteWindow(QObject * parent = 0);
    ~PasteWindow();

public slots:
    void newPaste();
    void cancelPaste();

private slots:
    void _pasteReady(QString name, QString content);

private:
    void deletePasteWindow();

signals:
    void pasteReady(QString filename, QString content);

private:
    QQmlEngine engine;
    QQmlComponent * component;
    QObject * window;

};

#endif // PASTEWINDOW_H
