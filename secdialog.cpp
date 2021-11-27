#include "secdialog.h"
#include "ui_secdialog.h"
#include "Raid5.h"

SecDialog::SecDialog(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::SecDialog)
{
    ui->setupUi(this);
    QPixmap pix("/home/rpi/Desktop/Picture/Sample Pictures/Chrysanthemum.jpg");
    ui->label_pic->setPixmap(pix);
}

SecDialog::~SecDialog()
{
    delete ui;
}
void SecDialog::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}


void SecDialog::on_pushButton_clicked()
{
    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName = QFileDialog::getOpenFileName(this,tr("Image Files (*.png *.jpg *.bmp)"));


    if(!fileName.isEmpty())
    {
        QImage image(fileName);
        ui->label_pic->setPixmap(QPixmap::fromImage(image));
    }

    this->raid.set_iPath(fileName.toStdString());
    this->raid.Striping();

    fileName.clear();

}


void SecDialog::on_pushButton_Previous_clicked()
{
    this->raid.possibleShowL();

    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName = QString::fromStdString(raid.showingImg);


    if(!fileName.isEmpty())
    {
        QImage image(fileName);
        ui->label_pic->setPixmap(QPixmap::fromImage(image));
    }
}


void SecDialog::on_pushButton_Next_clicked()
{
    this->raid.possibleShowP();

    QFileDialog dialog(this);
    dialog.setNameFilter(tr("Images (*.png *.xpm *.jpg)"));
    dialog.setViewMode(QFileDialog::Detail);
    QString fileName = QString::fromStdString(raid.showingImg);


    if(!fileName.isEmpty())
    {
        QImage image(fileName);
        ui->label_pic->setPixmap(QPixmap::fromImage(image));
    }

}

