#include "keyInput.h"
#include <Novice.h>

static char keys[256] = { 0 };
static char preKeys[256] = { 0 };

void CheckKey()
{
	memcpy(preKeys, keys, 256);
	Novice::GetHitKeyStateAll(keys);
}

bool EmptyKey(int Keys) {
	return !keys[Keys] && !preKeys[Keys];
}

bool TriggerKey(char Keys) {
	return keys[Keys] && !preKeys[Keys];
}

bool PressKey(int Keys) {
	return keys[Keys];
}

bool ReleaseKey(int Keys) {
	return !keys[Keys] && preKeys[Keys];
}