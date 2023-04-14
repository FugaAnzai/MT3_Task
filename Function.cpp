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
	//一行バッファ
	std::string line_buff;
	//一文字バッファ
	std::string buff;

	//ファイル読み込み
	std::ifstream read_file(path);

	int i = 0;

	//一行読み取り
	while (std::getline(read_file, line_buff)) {

		//一行バッファをgetlineに渡せるように変換
		std::istringstream line(line_buff);

		//,の後の数字読み取り
		while (std::getline(line, buff, ',')) {
			array[i] = std::stoi(buff);//値をarrayに保存
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