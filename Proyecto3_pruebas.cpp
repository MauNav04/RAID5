// Proyecto3_pruebas.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include<fstream>
#include<string>
#include<vector>
#include<bitset>
#include"Raid5.h"

using namespace std;

int main()
{
    string image_Path = "C:/Users/fantu/Documents/Semestre2-2021/Datos2/Proyecto3/Proyecto/Proyecto3_pruebas/asets/lineasH.png";
    string image_Path1 = "C:/Users/fantu/Documents/Semestre2-2021/Datos2/Proyecto3/Proyecto/Proyecto3_pruebas/asets/diagonales.png";
    string image_Path2 = "C:/Users/fantu/Documents/Semestre2-2021/Datos2/Proyecto3/Proyecto/Proyecto3_pruebas/asets/zigzag.bmp";

    Raid5 raid;
    raid.set_iPath(image_Path);
    raid.Striping();
    raid.set_iPath(image_Path1);
    raid.Striping();
    raid.set_iPath(image_Path2);
    raid.Striping();
    
    int whDisk;
    cout << " -> Which disk has to be rebuilded?" << endl;
    cin >> whDisk;
    raid.Rebuild(whDisk);

    int whImage;
    cout << "-> Which image would you like to see?" << endl;
    cin >> whImage;
    raid.Unstripping(whImage);

    /*int newUser = raid.add_User("Mauro");
    raid.add_File("Hola");
    raid.add_File("Hola");
    cout << newUser << endl;
    
    int newUser1 = raid.add_User("Mauro");
    cout << newUser1 << endl;
    
    int newUser2 = raid.add_User("Marta");
    raid.add_File("Hola");
    cout << newUser2 << endl;

    int newUser3 = raid.add_User("Pamela");
    raid.add_File("Hola");
    raid.add_File("Hola");
    raid.add_File("Hola");
    cout << newUser3 << endl;

    cout << raid.userNames.size() << endl;
    int currUsIndx = raid.userNames.size();
    cout << raid.userFiles[currUsIndx - 1][2];

    string currUser = raid.get_User();
    cout << currUser << endl;*/


    return 0;
}

