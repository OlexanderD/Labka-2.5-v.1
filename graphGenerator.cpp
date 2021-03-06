// LABKA 2.5 EDGES GENERATOR
#include <iostream>
#include <fstream>
#include <string>
#include <random>
#define NOMINMAX
#include <Windows.h>

void putInfo();
void makeFullPlainGR(std::ofstream&, const size_t& amountOfVertices);
void makeTrail(std::ofstream&, const size_t& amountOfVertices);
void makeTour(std::ofstream&, const size_t& amountOfVertices);
std::string getOutputFilePath();
size_t randomGenerator(size_t min, size_t max);

int main() {
	system("mode con COLS=700");
	ShowWindow(GetConsoleWindow(), SW_MAXIMIZE);
	SendMessage(GetConsoleWindow(), WM_SYSKEYDOWN, VK_RETURN, 0x20000000);
	
	putInfo();
	
	try {
		std::string graphType = "";
		std::cout << "\nWhat type of graph do you want:" <<
					 "\nFull plain (fp)" <<
					 "\nPlain trail (ptr)" << ", Plaint tour (pto)" <<
					 "\nOriented trail (otr)" << ", Oriented tour (oto)" << std::endl;
		while (true) {
			std::cout << ">> ";
			std::cin >> graphType;
			if (graphType != "fp" and graphType != "ptr" and graphType != "pto" and graphType != "otr" and graphType != "oto")
				graphType.clear();
			else
				break;
		}

		unsigned char connected = ' ';
		std::cout << "\nIs it connected? (Connected - C, Disconnected - D)" << std::endl;
		while (true) {
			std::cout << ">> ";
			std::cin >> connected;
			if (connected != 'C' and connected != 'c' and connected != 'D' and connected != 'd')
				connected = ' ';
			else
				break;
		}

		int amountOfVertices = 0;
		while (true) {
			std::cout << "\nEnter how many vertices you want (<= 50000): ";
			std::cin >> amountOfVertices;			
			if (amountOfVertices <= 0 or amountOfVertices > 50000) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
			} else
				break;
		}       

		std::ofstream outputFileS;
		while (true) {
			std::string outputFilePath = getOutputFilePath();
			outputFileS.open(outputFilePath);
			if (outputFileS.fail())
				outputFilePath.clear();
			else
				break;
		}

		if (connected == 'C' or connected == 'c')
			if (graphType == "fp") {
				outputFileS << '0' << ' ' << amountOfVertices << std::endl;
				makeFullPlainGR(outputFileS, amountOfVertices);
			} else if (graphType == "ptr") {
				outputFileS << '0' << ' ' << amountOfVertices << std::endl;
				makeTrail(outputFileS, amountOfVertices);
			} else if (graphType == "pto") {
				outputFileS << '0' << ' ' << amountOfVertices << std::endl;
				makeTour(outputFileS, amountOfVertices);
			} else if (graphType == "otr") {
				outputFileS << '1' << ' ' << amountOfVertices << std::endl;
				makeTrail(outputFileS, amountOfVertices);
			} else { // graphType == "oto"
				outputFileS << '1' << ' ' << amountOfVertices << std::endl;
				makeTour(outputFileS, amountOfVertices);
			}
		else {
			if (graphType == "pto" or graphType == "ptr")
				outputFileS << '0' << ' ' << amountOfVertices << std::endl;
			else
				outputFileS << '1' << ' ' << amountOfVertices << std::endl;
			for (size_t i = 0; i < amountOfVertices; ++i) {
				std::cout << "Processing..." << std::endl;
				outputFileS << randomGenerator(0, size_t(amountOfVertices) - 1) << ' '
					<< randomGenerator(0, size_t(amountOfVertices) - 1) << std::endl;
			}
		}
	} catch (const std::exception& ex) {
		std::cerr << "\n\t" << ex.what() << std::endl << std::endl;
		system("pause");
		return -1;
	}
	system("pause");
	return 0;
}

void putInfo() {
	std::cout << "#########################################\n" << 
				 "# GRAPH EDGES GENERATOR 2000ULTRARANDOM #\n" << 
				 "#########################################" << std::endl;
}

std::string getOutputFilePath() {
	std::string filePath = "";
	std::cout << "\nEnter the path to the output file or its name: ";
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
	getline(std::cin, filePath);
	//if file path is empty -> save the output to the out.txt in the root folder
	std::string rootFolder = "D:/Studying/Programming/LABS/Labka 2.5/Labka 2.5 text files/";
	if (filePath.empty())
		filePath = rootFolder + "out.txt";
	//if user didn't provided full adress -> create a new file in the root folder
	else if (filePath.find('\\') == std::string::npos and filePath.find('/') == std::string::npos) {
		filePath.insert(0, rootFolder); // prepend address of the root folder
		filePath.append(".txt"); // append extension of a text file
	}
	return filePath;
}

void makeFullPlainGR(std::ofstream& ofs, const size_t& amountOfVertices) {
	for (size_t i = 0; i < amountOfVertices; ++i)
		for (size_t j = 0; j < amountOfVertices; ++j)
			if (j > i) { // doesn't allow loops and repeats
				std::cout << "Processing..." << std::endl;
				ofs << i << ' ' << j << std::endl;
			}
}

void makeTrail(std::ofstream& ofs, const size_t& amountOfVertices) {
	std::vector<size_t> verticesArr(amountOfVertices);
	for (size_t i = 0; i < amountOfVertices; ++i)
		verticesArr[i] = i;
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(verticesArr.begin(), verticesArr.end(), g);
	size_t k = 0;
	while ((k + 1) < amountOfVertices) {
		ofs << verticesArr[k] << ' ';
		ofs << verticesArr[++k] << std::endl;
		std::cout << "Processing..." << std::endl;
	}
}

void makeTour(std::ofstream& ofs, const size_t& amountOfVertices) {
	std::vector<size_t> verticesArr(amountOfVertices);
	for (size_t i = 0; i < amountOfVertices; ++i)
		verticesArr[i] = i;
	std::random_device rd;
	std::mt19937 g(rd());
	std::shuffle(verticesArr.begin(), verticesArr.end(), g);
	size_t k = 0;
	while (true) {
		ofs << verticesArr[k] << ' ';
		if ((k + 1) != amountOfVertices)
			ofs << verticesArr[++k] << std::endl;
		else {
			ofs << verticesArr[0] << std::endl; 
			break;
		}
	}
}

size_t randomGenerator(size_t min, size_t max) {
	std::mt19937 rng;
	rng.seed(std::random_device()());
	std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
	return dist(rng);
}
