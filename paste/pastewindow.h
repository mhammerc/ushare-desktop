#ifndef PASTE_H
#define PASTE_H

#include <QApplication>
#include <QWidget>
#include <QPushButton>
#include <QTextEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include "shared.h"
#include "pastecontent.h"

class FileManager;

class PasteWindow : public QWidget
{
    Q_OBJECT
public:
    explicit PasteWindow(FileManager*, QWidget * qwidgetParent = 0);

protected:
    void setUpContextMenu();
    void setUpConnexion();

    QVBoxLayout * mainLayout;

    QHBoxLayout * fileNameLayout;
    QLabel * fileNameLabel;
    QLineEdit * fileNameLineEdit;

    QTextEdit * contentText;

    QHBoxLayout * bottomButtonLayout;
    ButtonBlue * send;
    ButtonBlue * cancel;

    //----

    FileManager * parent;

public slots:
    void sendTriggered();

signals:
};

#endif
