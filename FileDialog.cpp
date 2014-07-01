#include "FileDialog.h"


void FileDialog::closeEvent(QCloseEvent *event)
{
    event->ignore();
    this->hide();
}

FileDialog::FileDialog() {}


FileDialog::~FileDialog() {}
