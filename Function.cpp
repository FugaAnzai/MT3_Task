#include "Function.h"
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

int Function::clamp(int value, int min, int max) {

	if (value < min) {
		return min;
	}
	else if (value > max) {
		return max;
	}

	return value;
}

void Function::LoadCSV(const char* path, int* array) {
	
	std::string line_buff;
	
	std::string buff;

	
	std::ifstream read_file(path);

	int i = 0;

	
	while (std::getline(read_file, line_buff)) {

		
		std::istringstream line(line_buff);

		
		while (std::getline(line, buff, ',')) {
			array[i] = std::stoi(buff);
			i++;
		}
	}

}

void Function::Vector3ScreenPrintf(int x, int y, const Vector3& vector3, const char* label) {
	Novice::ScreenPrintf(x, y, "%.02f", vector3.x);
	Novice::ScreenPrintf(x + kColumnWidth, y, "%.02f", vector3.y);
	Novice::ScreenPrintf(x + kColumnWidth * 2, y, "%.02f", vector3.z);
	Novice::ScreenPrintf(x + kColumnWidth * 3, y, "%s", label);
}