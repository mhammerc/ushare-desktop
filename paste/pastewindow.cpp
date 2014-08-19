#include "pastewindow.h"
#include "screenmanager.h"

PasteWindow::PasteWindow(FileManager* parent, QWidget * qwidgetParent) : parent(parent), QWidget(qwidgetParent)
{
    setWindowTitle(Uplimg::applicationName);
    QIcon icon(":/icon/iconBase.png");
    setWindowIcon(icon);

    setUpContextMenu();
    setUpConnexion();
}

void PasteWindow::setUpContextMenu()
{
    /* file name */
    fileNameLayout = new QHBoxLayout;
    fileNameLabel = new QLabel(tr("PASTE_FILE_NAME"));
    fileNameLineEdit = new QLineEdit;
    //--
    fileNameLayout->addWidget(fileNameLabel);
    fileNameLayout->addWidget(fileNameLineEdit);

    /* content text */
    contentText = new QTextEdit;

    /* bottom button */
    bottomButtonLayout = new QHBoxLayout;
    cancel = new ButtonBlue(tr("PASTE_CANCEL"));
    send = new ButtonBlue(tr("PASTE_SEND"));
    //--
    bottomButtonLayout->addStretch();
    bottomButtonLayout->addWidget(cancel);
    bottomButtonLayout->addWidget(send);

    //||
    mainLayout = new QVBoxLayout;
    mainLayout->addLayout(fileNameLayout);
    mainLayout->addWidget(contentText);
    mainLayout->addLayout(bottomButtonLayout);

    setLayout(mainLayout);
}

void PasteWindow::setUpConnexion()
{
    QObject::connect(cancel, SIGNAL(clicked()), this, SLOT(deleteLater()));
    QObject::connect(send, SIGNAL(clicked()), this, SLOT(sendTriggered()));
}

void PasteWindow::sendTriggered()
{
    PasteContent content;
    content.fileTitle = fileNameLineEdit->text();
    content.fileContent = contentText->toPlainText();
    parent->pasteReady(content);
}
