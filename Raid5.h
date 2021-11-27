#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<vector>
#include<bitset>

using namespace std;

class Raid5
{
public:
	//===== Atributes =====//
	/**
	* @brief helds the path of an image as a string
	*/
	string imagePath;
	/**
	* @brief string that locates the root folders where the raid will work
	*/
    string disksPath = "C:/Users/fantu/Desktop/LoginApp/LoginApp/raid5/DISCO";

    string ImStoragePath = "C:/Users/fantu/Desktop/LoginApp/LoginApp/builtImg";

    string showingImg;
	/**
	* @brief counter that indicates how many documents are being holded by the raid
	*/
	int docIndex = 0;
	/**
	* @brief counter that determines where the parity file will be for each strip
	*/
	int parityIndex = 4;
	/**
	* @brief counter that determines which user is uploading an image
	*/
	int currentUser;

    int shownImage = 0;

	//===== Methods =====//
	// constructor
	Raid5();
	/**
	* @brief Sets a path to read an image.
	* @param [string] requires a path for an image
	*/
	int add_User(string name);

	string get_User();

	void add_File(string bytes);

	void send_to_database();

	void set_iPath(string iPath);
	/**
	* @brief overload method - Automatcally intends to read the image Path
	* @param no parameters needed
	* @return returns a string with the contents of the image represented on binary format
	*/
	string ReadFile();
	/**
	* @brief overloaded method - Reads the file on a given path.
	* @param [string] requires a path for the file that is wanted to be read
	* @return returns a string with the contents of the file represented on binary format
	*/
	string ReadFile(string fPath);
	/**
	* @brief Writes a file on binary format.
	* @param [string] Path which represents the place where te image will be written and its name
	* @param [string] Data that will be written on the file
	*/
	void WriteFile(string fPath, string wData);
	/**
	* @brief Updates the place where the parity will be placed on the next strip.
	* @param no parameters are needed
	*/
	void UpdateParityIndex();
	/**
	* @brief When an image is being unstripped or rebuilded, calculates the placer where its parity'd be.
	* @param [int] indicating the number of the file that wants to be retrieved
	* @return [int] indicating the disk where the parity file is located for the given fileIndex
	*/
	int CalculateParity(int fileIndex);
	/**
	* @brief When a disk is being rebuilded, indicates which part of the current file was missing at this disk
	* @param [int] indicating the disk where the pairty of this file is located
	* @param [int] indicating which is the missing disk
	* @return [int] indicating the part of the file that has to be reconstructed
	*/
	int CalculateMissingPart(int parity4file, int diskIndex);
	/**
	* @brief Stripes the image that is currently loaded on to 3 parts and calls for parity generating method.
	*		 When striping is finished, the Disks will have a part of the image each, as well as the parity file
	* @param no parameters needed
	*/
	void Striping();

	void Striping(string binData);

    int getShown();

    void possibleShowP();

    void possibleShowL();

    /**
	* @brief When given an image Index, it searches for the parts of that image and puts the together, and generates the image file
	* @param [int] Indicating the index of the image that will be reconstructed 
	* @return [int] Indicating that the image was built. Returns -1 if the image is not on stored on the raid
	*/
	int Unstripping(int retrievedIndex);


	/**
	* @brief Overloaded method. When an image has been striped, it generates the parity file for this image
	* @param [vector<string>] The vector holds the paths were the parts of the image are stored
	*/
	void GenParity(vector<string> stPaths);
	/**
	* @brief Overloaded method. When an image is being reconstructed, it generates the parity file for this image
	* @param [vector<string>] The vector holds the paths were the parts of the image are stored
	* @param [int] indicating the disk where the parity file is stored
	* @param [int] indicating the which document the parity is being generated for
	*/
	void GenParity(vector<string> stPaths, int parity4file, int doc4file);
	/**
	* @brief When a diskIndex is given, the files that were stored on that disk will be reconstructed
	* @param [int] Indicating the disk were the files are missing
	*/
	void Rebuild(int diskIndex);

};

