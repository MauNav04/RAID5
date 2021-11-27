#include "Raid5.h"

Raid5::Raid5()
{
}

//int Raid5::add_User(string in_name)
//{
//    for (string name : this->userNames)
//    {
//        if (in_name == name)
//        {
//            return -1;
//        }
//    }
//    this->userNames.push_back(in_name);
    
//    for (int i = 0; i < this->userNames.size(); i++)
//    {
//        if (this->userNames[i] == in_name)
//        {
//            this->currentUser = i;
//        }
//    }

//    return 0;
//}

//string Raid5::get_User()
//{
//    for (int i = 0; i < this->userNames.size(); i++)
//    {
//        if (i == this->currentUser)
//        {
//            return this->userNames[i];
//        }
//    }
//}

void Raid5::add_File(string bytes)
{
    //this->Striping(bytes);
    this->docIndex++;
    //this->userFiles[this->currentUser].push_back(this->docIndex);
    //this->send_to_database();

    /*if (this->userFiles.size() < this->userNames.size()) 
    {
        vector<int> newStorage;
        newStorage.push_back(this->docIndex);
        this->userFiles[this->currentUser].push_back(newStorage);
    }
    else if(this->userFiles.size() == this->userNames.size())
    {
        int lastAdd = this->userFiles[this->currentUser].size();
        this->userFiles[this->currentUser][lastAdd].push_back(this->docIndex);
    }*/

}

//void Raid5::send_to_database()
//{
//    string currUsername = this->get_User();
//    int currImageIndex = this->docIndex;
//}

void Raid5::set_iPath(string iPath)
{
	this->imagePath = iPath;
}

string Raid5::ReadFile()
{
    std::ifstream fin(this->imagePath, std::ios::binary);
    fin.seekg(0, std::ios::end);
    std::string data;
    int reSize = fin.tellg();
    data.resize(reSize);
    fin.seekg(0, std::ios::beg);
    fin.read(&data[0], data.size());

    this->docIndex++;
    this->shownImage++;

    return data;
}

string Raid5::ReadFile(string fPath)
{
    std::ifstream fin(fPath, std::ios::binary);
    fin.seekg(0, std::ios::end);
    std::string data;
    int reSize = fin.tellg();
    data.resize(reSize);
    fin.seekg(0, std::ios::beg);
    fin.read(&data[0], data.size());

    return data;
}

void Raid5::WriteFile(string fPath, string wData)
{
    ofstream resFile(fPath, ios::out | ios::binary);

    for (int i = 0; i < wData.length(); i++)
    {
        resFile.put(wData[i]);
    }

    cout << "-> A file has been written" << endl;

    resFile.clear();
}

void Raid5::UpdateParityIndex()
{
    if (this->parityIndex == 4)
    {
        this->parityIndex = 1;
    }
    else parityIndex++;
}

int Raid5::CalculateParity(int fileIndex)
{
    int counter = 4;
    int docReviewed = 1;

    for (int i = 0; i < this->docIndex; i++)
    {
        if (docReviewed == fileIndex)
        {
            return counter;
        }
        else if (counter == 4) 
        {
            counter = 1;
        }
        else 
        {
            counter++;
        }
        docReviewed++;
    }
    return -1;
}

int Raid5::CalculateMissingPart(int parity4file, int diskIndex)
{
    int diskCont = 1;
    int partCont = 1;

    for (int i = 1; i <= 4; i++)
    {
        if (diskCont == diskIndex)
        {
            return partCont;
        }
        else if (diskCont == parity4file)
        {
            diskCont++;
        }
        else
        {
            diskCont++;
            partCont++;
        }
    }

    return 0;
}

void Raid5::Striping()
{
    string binData = ReadFile();

    vector<string> strippedPaths;

    int counter = 0;
    int diskIndex = 1;
    int partIndex = 1;
    int counter2 = 0;
    int dataLen = binData.length();
    int usefulLen = dataLen;

    while (usefulLen % 3 != 0)
    {
        usefulLen++;
    }

    int divideParameter = usefulLen / 3;

    while (counter < usefulLen)
    {
        if (diskIndex == this->parityIndex)
        {
            diskIndex++;
        }
        string fileName = this->disksPath + to_string(diskIndex) + "/" + to_string(this->docIndex) + "." + to_string(partIndex) + ".txt";

        ofstream stripFile(fileName, ios::out | ios::binary);

        if (counter + divideParameter > dataLen)
        {
            for (int i = 0; i < dataLen + 1 - counter; i++)
            {
                stripFile.put(binData[counter + i]);
            }
            stripFile.put(this->currentUser);

            stripFile.close();
        }
        else
        {
            for (int i = 0; i < divideParameter; i++)
            {
                stripFile.put(binData[counter + i]);
            }
            stripFile.put(this->currentUser);
            stripFile.close();
        }

        cout << "-> Convertion form bin to text for file # " << this->docIndex << " is done" << endl;

        stripFile.clear();
        diskIndex++;
        partIndex++;
        counter += divideParameter;

        strippedPaths.push_back(fileName);
    }
    
    this->GenParity(strippedPaths);
}

void Raid5::Striping(string binData)
{
    this->docIndex++;

    vector<string> strippedPaths;

    int counter = 0;
    int diskIndex = 1;
    int partIndex = 1;
    int counter2 = 0;
    int dataLen = binData.length();
    int usefulLen = dataLen;

    while (usefulLen % 3 != 0)
    {
        usefulLen++;
    }

    int divideParameter = usefulLen / 3;

    while (counter < usefulLen)
    {
        if (diskIndex == this->parityIndex)
        {
            diskIndex++;
        }
        string fileName = this->disksPath + to_string(diskIndex) + "/" + to_string(this->docIndex) + "." + to_string(partIndex) + ".txt";

        ofstream stripFile(fileName, ios::out | ios::binary);

        if (counter + divideParameter > dataLen)
        {
            for (int i = 0; i < dataLen - counter; i++)
            {
                stripFile.put(binData[counter + i]);
            }
            stripFile.put(this->currentUser);
        }
        else
        {
            for (int i = 0; i < divideParameter; i++)
            {
                stripFile.put(binData[counter + i]);
            }
            stripFile.put(this->currentUser);
        }

        cout << "-> Convertion form bin to text for file # " << this->docIndex << " is done" << endl;

        stripFile.clear();
        diskIndex++;
        partIndex++;
        counter += divideParameter;

        //strippedPaths.push_back(fileName);
    }

    this->GenParity(strippedPaths);
}

int Raid5::getShown()
{
    int a = this->shownImage;
    return a;
}

void Raid5::possibleShowP()
{
    int possible = this->getShown();
    this->Unstripping(possible += 1);

}

void Raid5::possibleShowL()
{
    cout << "pos img: " << shownImage << endl;
    int possible = this->getShown();
    cout << "pos img: " << shownImage << endl;
    this->Unstripping(possible -= 1);
    cout << "Estamos en la fama" << endl;
}

int Raid5::Unstripping(int retrievedIndex)
{
    if(retrievedIndex < 1 || retrievedIndex > this->docIndex)
    {
        cout << "error"<< endl;
        return -1;
    }

    int parity4file = this->CalculateParity(retrievedIndex);

//    if (parity4file < 0)
//    {
//        cout << "** ERROR: The solicited image is out of the range of the gallery";
//        return -1;
//    }

    this->shownImage = retrievedIndex;

    vector<string> retrievedPaths;
    int diskRetrieved = 1;
    int partRetrieved = 1;

    for (int i = 0; i < 3; i++)
    {
        if (diskRetrieved == parity4file) { diskRetrieved++; }
        string creatingPath = this->disksPath + to_string(diskRetrieved) + "/" + to_string(retrievedIndex) + "." + to_string(partRetrieved) + ".txt";
        retrievedPaths.push_back(creatingPath);
        creatingPath.clear();
        diskRetrieved++;
        partRetrieved++;
    }

    string byteA1 = ReadFile(retrievedPaths[0]);
    string byteA2 = ReadFile(retrievedPaths[1]);
    string byteA3 = ReadFile(retrievedPaths[2]);

    byteA1.pop_back();
    byteA2.pop_back();
    byteA3.pop_back();

    string total_image_bytes = byteA1 + byteA2 + byteA3;

    string deployingPath = this->ImStoragePath + "/" + to_string(this->shownImage) + ".png";

    WriteFile(deployingPath, total_image_bytes);

    this->showingImg = deployingPath;

    cout << "-> Unstripping's been finished" << endl;

    return 0;
}


void Raid5::GenParity(vector<string> stPaths)
{
    string byteA1 = ReadFile(stPaths[0]);
    string byteA2 = ReadFile(stPaths[1]);
    string byteA3 = ReadFile(stPaths[2]);

    string xor1;
    xor1.resize(static_cast<int>(byteA1.length()));

    string xorP;
    xorP.resize(static_cast<int>(byteA1.length()));

    for (int i = 0; i < static_cast<int>(byteA1.length()); i++)
    {
        int b1 = static_cast<int>(byteA1[i]);
        int b2 = static_cast<int>(byteA2[i]);
        int res = b1 ^ b2;
        xor1[i] = res;
    }

    for (int i = 0; i < (int)byteA2.length(); i++)
    {
        xorP[i] = (int)xor1[i] ^ (int)byteA3[i];
    }

    string fileName = this->disksPath + to_string(this->parityIndex) + "/p" + to_string(this->docIndex) + ".txt";

    this->WriteFile(fileName, xorP);

    this->UpdateParityIndex();

    cout << "-> A parity file has been generated" << endl;
}

void Raid5::GenParity(vector<string> stPaths, int parity4file, int doc4file)
{
    string byteA1 = ReadFile(stPaths[0]);
    string byteA2 = ReadFile(stPaths[1]);
    string byteA3 = ReadFile(stPaths[2]);

    string xor1;
    xor1.resize(byteA1.length());

    string xorP;
    xorP.resize(byteA1.length());

    for (int i = 0; i < byteA1.length(); i++)
    {
        int b1 = (int)byteA1[i];
        int b2 = (int)byteA2[i];
        int res = b1 xor b2;
        xor1[i] = static_cast<char> (res);
    }

    for (int i = 0; i < byteA2.length(); i++)
    {
        xorP[i] = (int)xor1[i] ^ (int)byteA3[i];
    }

    string fileName = this->disksPath + to_string(parity4file) + "/p" + to_string(doc4file) + ".txt";

    this->WriteFile(fileName, xorP);

    cout << "The parity file for image # " << doc4file << " has been reconstructed" << endl;
}

void Raid5::Rebuild(int diskIndex)
{
    for (int i = 1; i <= this->docIndex; i++)
    {
        int parity4file = this->CalculateParity(i);
        vector<string> retrievedPaths;
        if (parity4file == diskIndex)
        {
            int diskRetrieved = 1;
            int partRetrieved = 1;

            for (int j = 0; j < 3; j++)
            {
                if (diskRetrieved == diskIndex) { diskRetrieved++; }
                string creatingPath = this->disksPath + to_string(diskRetrieved) + "/" + to_string(i) + "." + to_string(partRetrieved) + ".txt";
                retrievedPaths.push_back(creatingPath);
                creatingPath.clear();
                diskRetrieved++;
                partRetrieved++;
            }
            
            this->GenParity(retrievedPaths, parity4file, i);
            retrievedPaths.clear();
        }

        else
        {
            int diskRetrieved = 1;
            int partRetrieved = 1;
            int missingPart = this->CalculateMissingPart(parity4file, diskIndex);

            for (int j = 0; j < 3; j++)
            {
                if (diskRetrieved == diskIndex) { diskRetrieved++; }
                if (partRetrieved == missingPart) { partRetrieved++; }
                if (diskRetrieved == parity4file)
                {
                    string creatingPath = this->disksPath + to_string(diskRetrieved) + "/" + "p" + to_string(i) + ".txt";
                    retrievedPaths.push_back(creatingPath);
                    creatingPath.clear();
                    diskRetrieved++;
                }
                else
                {
                    string creatingPath = this->disksPath + to_string(diskRetrieved) + "/" + to_string(i) + "." + to_string(partRetrieved) + ".txt";
                    retrievedPaths.push_back(creatingPath);
                    creatingPath.clear();
                    diskRetrieved++;
                    partRetrieved++;
                }
                
            }

            string byteA1 = ReadFile(retrievedPaths[0]);
            string byteA2 = ReadFile(retrievedPaths[1]);
            string byteA3 = ReadFile(retrievedPaths[2]);

            retrievedPaths.clear();

            string xor1;
            xor1.resize(byteA1.length());

            string xorP;
            xorP.resize(byteA1.length());

            for (int j = 0; j < byteA1.length(); j++)
            {
                int b1 = (int)byteA1[j];
                int b2 = (int)byteA2[j];
                int res = b1 xor b2;
                xor1[j] = static_cast<char> (res);
            }

            for (int j = 0; j < byteA2.length(); j++)
            {
                xorP[j] = (int)xor1[j] ^ (int)byteA3[j];
            }

            string fileName = this->disksPath + to_string(diskIndex) + "/" + to_string(i) + "." + to_string(missingPart) + ".txt";

            this->WriteFile(fileName, xorP);

            cout << "Se reconstruyó parte " << missingPart << " para el archivo # " << i << endl;
        }
    }
}
