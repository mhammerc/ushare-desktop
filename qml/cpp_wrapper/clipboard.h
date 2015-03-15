#ifndef DESKTOP_H
#define DESKTOP_H

#include <QApplication>
#include <QObject>
#include <QString>
#include <QClipboard>

class Clipboard : public QObject
{
    Q_OBJECT

public:
    Clipboard(QObject * parent = 0) : QObject(parent) {}

    Q_INVOKABLE void setText(QString text)
    {
        QClipboard * clipboard = QApplication::clipboard();
        clipboard->setText(text);
    }
};

#endif // DESKTOP_H

