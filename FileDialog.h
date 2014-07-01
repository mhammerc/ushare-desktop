#pragma once

#include <QFileDialog>
#include <QCloseEvent>

class FileDialog :
    public QFileDialog
{
public:
    FileDialog();
    ~FileDialog();

protected:
    virtual void closeEvent(QCloseEvent *event);
};

