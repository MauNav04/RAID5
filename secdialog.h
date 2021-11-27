#ifndef SECDIALOG_H
#define SECDIALOG_H
#include <QFileDialog>
#include <QLabel>
#include "Raid5.h"
#include <QMainWindow>

namespace Ui {
class SecDialog;
}

class SecDialog : public QMainWindow
{
    Q_OBJECT

public:
    Raid5 raid;
    explicit SecDialog(QWidget *parent = nullptr);
    ~SecDialog();

protected:
    void changeEvent(QEvent *e);

private slots:
    void on_pushButton_clicked();

    void on_pushButton_Previous_clicked();

    void on_pushButton_Next_clicked();

private:
    Ui::SecDialog *ui;
};

#endif // SECDIALOG_H
