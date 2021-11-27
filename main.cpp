#include "mainwindow.h"
#include <QtGui/QApplicationStateChangeEvent>
#include <QApplication>
#include <Raid5.h>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();

//    string image_Path = "C:/Users/fantu/Documents/Semestre2-2021/Datos2/Proyecto3/Proyecto/Proyecto3_pruebas/asets/lineasH.png";
//    string image_Path1 = "C:/Users/fantu/Documents/Semestre2-2021/Datos2/Proyecto3/Proyecto/Proyecto3_pruebas/asets/diagonales.png";
//    string image_Path2 = "C:/Users/fantu/Documents/Semestre2-2021/Datos2/Proyecto3/Proyecto/Proyecto3_pruebas/asets/zigzag.bmp";

//    Raid5 raid;
//    raid.set_iPath(image_Path);
//    raid.Striping();
//    raid.set_iPath(image_Path1);
//    raid.Striping();
//    raid.set_iPath(image_Path2);
//    raid.Striping();

//    int whDisk;
//    cout << " -> Which disk has to be rebuilded?" << endl;
//    cin >> whDisk;
//    raid.Rebuild(whDisk);

//    int whImage;
//    cout << "-> Which image would you like to see?" << endl;
//    cin >> whImage;

//    raid.possibleShowP();
//    raid.possibleShowL();
}
