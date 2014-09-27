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

    languageSelector = new ComboBoxBlue;
    languageSelector->addItem("Classic text", "text");
    languageSelector->addItem("ActionScript3", "as3");
    languageSelector->addItem("Bash/shell (linux/unix)", "bash");
    languageSelector->addItem("ColdFusion", "coldfusion");
    languageSelector->addItem("C#", "csharp");
    languageSelector->addItem("C", "c");
    languageSelector->addItem("C++", "cpp");
    languageSelector->addItem("CSS", "css");
    languageSelector->addItem("Delphi", "delphi");
    languageSelector->addItem("Diff", "diff");
    languageSelector->addItem("Erlang", "erlang");
    languageSelector->addItem("Groovy", "groovy");
    languageSelector->addItem("HTML", "html");
    languageSelector->addItem("JavaScript", "javascript");
    languageSelector->addItem("Java", "java");
    languageSelector->addItem("JavaFX", "javafx");
    languageSelector->addItem("Perl", "perl");
    languageSelector->addItem("PHP", "php");
    languageSelector->addItem("PowerShell", "powershell");
    languageSelector->addItem("Python", "python");
    languageSelector->addItem("Ruby", "ruby");
    languageSelector->addItem("Scala", "scala");
    languageSelector->addItem("SQL", "sql");
    languageSelector->addItem("Visual Basic", "vbnet");
    languageSelector->addItem("XML", "xml");
    languageSelector->setCurrentIndex(settings.value(Reg::pasteLastLanguageSelected).toInt());
    QObject::connect(languageSelector, SIGNAL(currentIndexChanged(int)), this, SLOT(languageIndexChanged(int)));
    //--
    fileNameLayout->addWidget(fileNameLabel);
    fileNameLayout->addWidget(fileNameLineEdit);
    fileNameLayout->addWidget(languageSelector);

    /* content text */
    contentText = new QTextEdit;
    contentText->setTabStopWidth(15);

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
    if(fileNameLineEdit->isModified())
        content.fileTitle = fileNameLineEdit->text();
    content.fileContentLanguage = languageSelector->currentData().toByteArray();
    content.fileContentLanguageHR = languageSelector->currentText();
    content.fileContent = contentText->toPlainText();
    parent->pasteReady(content);
}

void PasteWindow::languageIndexChanged(int index)
{
    settings.setValue(Reg::pasteLastLanguageSelected, index);
}
