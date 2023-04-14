#pragma once
#include <Novice.h>
#include "Vector3.h"

static const int kRowHeight = 20;
static const int kColumnWidth = 60;

namespace Function {
	int clamp(int value, int min, int max);
	void LoadCSV(const char* path, int* array);
	void Vector3ScreenPrintf(int x, int y, const Vector3& vector3, const char* label);
}