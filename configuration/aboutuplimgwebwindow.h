#ifndef ABOUTUPLIMGWEBWINDOW_H
#define ABOUTUPLIMGWEBWINDOW_H

#include <QDialog>

namespace Ui {
class AboutUplimgWebWindow;
}

class AboutUplimgWebWindow : public QDialog
{
    Q_OBJECT

public:
    explicit AboutUplimgWebWindow(QWidget *parent = 0);
    ~AboutUplimgWebWindow();

private slots:
    void on_buttonBox_windowIconTextChanged(const QString &iconText);

    void on_pushButton_clicked();

private:
    Ui::AboutUplimgWebWindow *ui;
};

#endif // ABOUTUPLIMGWEBWINDOW_H
