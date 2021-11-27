#include "mainwindow.h"
#include "secdialog.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

QStringList usuarios = {"test"};
QStringList contrasenas = {"test"};


void MainWindow::on_pushButton_login_clicked()
{
    QString username = ui->lineEdit_username->text();
    QString password = ui->lineEdit_password->text();




    if(username == "test"&& password == "test")
    {
        QMessageBox::information(this, "Login", "Username and password is correct");
        hide();
        secDialog = new SecDialog(this);
        secDialog->show();

    }
    else
    {
        QMessageBox::warning(this, "Login","Username an password is not corrrect");
    }
}

