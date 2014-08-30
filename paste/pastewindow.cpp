/**
This file (c) by : - Martin Hammerchmidt alias Imote

This file is licensed under a
Creative Commons Attribution-NonCommercial-ShareAlike 4.0 International License.

You should have received a copy of the license along with this
work. If not, see <http://creativecommons.org/licenses/by-nc-sa/4.0/>.

If you have contributed to this file, add your name to authors list.
*/

#include "pastewindow.h"
#include "screenmanager.h"

PasteWindow::PasteWindow(FileManager* parent, QWidget * qwidgetParent) : QWidget(qwidgetParent), parent(parent)
{
    setWindowTitle(Uplimg::applicationName);
    QIcon icon(":/icon/iconBase.png");
    setWindowIcon(icon);

    setUpWidgets();
    setUpConnections();
}

void PasteWindow::setUpWidgets()
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

void PasteWindow::setUpConnections()
{
    QShortcut * enterShortcut = new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Return), this);
    QObject::connect(enterShortcut, SIGNAL(activated()), this, SLOT(sendTriggered()));
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
