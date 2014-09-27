#include "aboutuplimgwebwindow.h"
#include "ui_aboutuplimgwebwindow.h"

AboutUplimgWebWindow::AboutUplimgWebWindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AboutUplimgWebWindow)
{
    ui->setupUi(this);
}

AboutUplimgWebWindow::~AboutUplimgWebWindow()
{
    delete ui;
}

void AboutUplimgWebWindow::on_buttonBox_windowIconTextChanged(const QString &iconText)
{

}

void AboutUplimgWebWindow::on_pushButton_clicked()
{
    this->hide();
}
