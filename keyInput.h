#pragma once

//毎フレームキーの更新
void CheckKey();
//キー入力
bool EmptyKey(int Keys);
bool TriggerKey(char Keys);
bool PressKey(int Keys);
bool ReleaseKey(int Keys);