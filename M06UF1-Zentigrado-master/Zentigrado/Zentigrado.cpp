// Zentigrado.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <string>
#include<map>
int ReadFile();
float version = 0.5f;
std::string title;
int texture_num = -1;

std::map<char, std::string>texture_files;

int level_width = 0;
int level_height = 0;

char** level;
char** level_floor;
int** level_collission;
char** level_object;

int main()
{
	std::cout << "Hello World!\n";
	ReadFile();
}
int ReadFile() {
	std::ifstream inputFile;

	inputFile.open("level1.zen");

	if (!inputFile.is_open()) {
		std::cout << "ERROR[1] File doesn't exist";
		return 1;
	}

	//reading header
	std::string data;

	getline(inputFile, data, ';');
	if (data != "ZEN") {
		std::cout << "ERROR[2] WRONG HEADER";
		return 2;
	}
	std::cout << data << std::endl;

	//reading version
	getline(inputFile, data, ';');

	float tmp = stof(data);

	//getline(inputFile, value, ';');
	if (tmp != version) {
		std::cout << "ERROR[3] WRONG VERSION";
		return 3;
		version = tmp;
	}
	std::cout << data << std::endl;
	
	//reading title
	getline(inputFile, data, ';');
	getline(inputFile, data, '\n');
	getline(inputFile, data, ';');

	if (data != "TITLE") {
		std::cout << "ERROR[4] NOT TITLE PROVIDED";
		return 4;
	}

	std::cout << data;
	
	//reading title name
	getline(inputFile, data, ';');
	if (data == "" || data == " ") {
		std::cout << "ERROR[5] BLANK TITLE";
		return 5;
	}
	//saving title
	title = data;
	std::cout << ": " << title << std::endl;

	//reading textures
	getline(inputFile, data, '\n');
	getline(inputFile, data, ';');

	if (data != "TEXTURES") {
		std::cout << "ERROR[6] TEXTURES NOT FOUND";
		return 6;
	}
	std::cout << data;

	//reading total of textures
	getline(inputFile, data, ';');

	texture_num = std::stoi(data);
	if (texture_num <= 0) {
		std::cout << "ERROR[7] TEXTURES NOT READ CORRECTLY";
		return 7;
	}

	std::cout << ": " << texture_num << std::endl;

	getline(inputFile, data,'\n');

	for (int i = 0; i < texture_num; i++) {
		//Reading the texture key value
		getline(inputFile, data, ';');

		if (data == "" || data.length() != 1) {
			std::cout << "ERROR[8] CAN'T READ DATA";
			return 8;
		}
		char texture_key = data[0];

		//Reading texture's name
		getline(inputFile, data, ';');
		if (data == "") {
			std::cout << "ERROR[9] CAN'T READ TEXTURE FILE";
		}

		std::string texture_file = data;

		texture_files.insert({texture_key, texture_file });

		std::cout << texture_key << ":" << texture_file << std::endl;

		getline(inputFile, data, '\n');
	}

	//Reading level values
	getline(inputFile, data, ';');
	if (data != "LEVEL") {
		std::cout << "ERROR[10] LEVEL NOT FOUND";
		return 10;
	}

	std::cout << data;

	//Reading level weight
	getline(inputFile, data, ';');
	level_width = std::stoi(data);
	if (level_width < 1) {
		std::cout << "ERROR[11] CAN'T READ LEVEL WEIGHT";
		return 11;
	}
	
	//Reading level height
	getline(inputFile, data, ';');
	level_height = std::stoi(data);
	if (level_height < 1) {
		std::cout << "ERROR[12] CAN'T READ LEVEL HEIGHT";
		return 12;
	}
	std::cout << ":" << level_width << "-" << level_height << std::endl;


	level = new char* [level_height];

	for (int i = 0; i < level_height; i++) {
		level[i] = new char[level_width];
	}

	getline(inputFile, data, '\n');

	for (int i = 0; i < level_height; i++) {
		for (int j = 0; j < level_width; j++) {
			getline(inputFile, data, ';');
			
			if (data == "" || data.length() != 1) {
				std::cout << "ERROR[13] CAN'T READ SQUARE: " << i << "-" << j << " IN LEVEL";
				return 13;
			}

			level[i][j] = data[0];

			std::cout << data[0];
		}

 		getline(inputFile, data, '\n');

		std::cout << std::endl;
	}

	//Reading floor values
	getline(inputFile, data, ';');
	if (data != "FLOOR") {
		std::cout << "ERROR[14] FLOOR NOT FOUND";
		return 14;
	}

	level_floor = new char* [level_height];

	for (int i = 0; i < level_height; i++) {
		level_floor[i] = new char[level_width];
	}

	getline(inputFile, data, '\n');

	for (int i = 0; i < level_height; i++) {
		for (int j = 0; j < level_width; j++) {
			getline(inputFile, data, ';');

			if (data == "" || data.length() != 1) {
				std::cout << "ERROR[15] CAN'T READ SQUARE: " << i << "-" << j << " IN FLOOR";
				return 15;
			}

			level_floor[i][j] = data[0];

			std::cout << data[0];
		}

		getline(inputFile, data, '\n');

		std::cout << std::endl;
	}

	//Reading collissions values
	getline(inputFile, data, ';');
	if (data != "COLLISSIONS") {
		std::cout << "ERROR[16] COLLISSIONS NOT FOUND";
		return 16;
	}

	level_collission = new int* [level_height];

	for (int i = 0; i < level_height; i++) {
		level_collission[i] = new int[level_width];
	}

	getline(inputFile, data, '\n');

	for (int i = 0; i < level_height; i++) {
		for (int j = 0; j < level_width; j++) {
			getline(inputFile, data, ';');

			if (data == "" || data.length() != 1) {
				std::cout << "ERROR[17] CAN'T READ SQUARE: " << i << "-" << j << " IN COLLISSION";
				return 17;
			}

			level_collission[i][j] = data[0];

			std::cout << data[0];
		}

		getline(inputFile, data, '\n');

		std::cout << std::endl;
	}
	

	//Reading collissions values
	getline(inputFile, data, ';');
	if (data != "OBJECTS") {
		std::cout << "ERROR[18] OBJECTS NOT FOUND";
		return 18;
	}

	level_object = new char* [level_height];

	for (int i = 0; i < level_height; i++) {
		level_object[i] = new char[level_width];
	}

	getline(inputFile, data, '\n');

	for (int i = 0; i < level_height; i++) {
		for (int j = 0; j < level_width; j++) {
			getline(inputFile, data, ';');

			if (data == "" || data.length() != 1) {
				std::cout << "ERROR[19] CAN'T READ SQUARE: " << i << "-" << j << " IN OBJECTS";
				return 19;
			}

			level_object[i][j] = data[0];

			std::cout << data[0];
		}

		getline(inputFile, data, '\n');

		std::cout << std::endl;
	}

	inputFile.close();
	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file