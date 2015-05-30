#include "pastewindow.h"

PasteWindow::PasteWindow(QObject * parent) : QObject(parent)
{
    component = new QQmlComponent(&engine, QUrl::fromLocalFile("qml/pastes/PasteWindow.qml"));
    qDebug() << component->errorString();
}

PasteWindow::~PasteWindow()
{
    if(!window)
        return;

    deletePasteWindow();
}

void PasteWindow::newPaste()
{
    if(window)
    {
        window->setProperty("visible", true);
        return;
    }

    window = component->create();
    window->setProperty("visible", true);

    QObject::connect(window, SIGNAL(send(QString, QString)), this, SLOT(_pasteReady(QString, QString)));
    QObject::connect(window, SIGNAL(cancel()), this, SLOT(cancelPaste()));
}

void PasteWindow::cancelPaste()
{
    deletePasteWindow();
}

void PasteWindow::_pasteReady(QString name, QString content)
{
    emit pasteReady(name, content);
    deletePasteWindow();
}

void PasteWindow::deletePasteWindow()
{
    window->setProperty("visible", false);
    window->deleteLater();
    window = nullptr;
}
