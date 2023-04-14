#include <Novice.h>
#include "keyInput.h"
#include "Function.h"
#include "Vector3.h"

const char kWindowTitle[] = "LD2A_01_アンザイフウガ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 v1 = Vector3(1.0f, 3.0f, -5.0f);
	Vector3 v2 = Vector3(4.0f, -1.0f, 2.0f);
	float k = 4.0f;

	Vector3 resultAdd = Vector3::Add(v1, v2);
	Vector3 resultSubtract = Vector3::Subtract(v1, v2);
	Vector3 resultMultiply = Vector3::Multiply(k, v1);
	float resultDot = Vector3::Dot(v1, v2);
	float resultLength = Vector3::Length(v1);
	Vector3 resultNormalize = Vector3::Normalize(v2);

	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		CheckKey();

		///
		/// ↓更新処理ここから
		///

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		Function::Vector3ScreenPrintf(0, 0, resultAdd, ": Add");
		Function::Vector3ScreenPrintf(0, kRowHeight, resultSubtract, ": Subtract");
		Function::Vector3ScreenPrintf(0, kRowHeight * 2, resultMultiply, ": Multiply");
		Novice::ScreenPrintf(0, kRowHeight * 3, "%.02f : Dot", resultDot);
		Novice::ScreenPrintf(0, kRowHeight * 4, "%.02f : Length", resultLength);
		Function::Vector3ScreenPrintf(0, kRowHeight * 5, resultNormalize, ": Normalize");

		///
		/// ↑描画処理ここまで
		///

		// フレームの終了
		Novice::EndFrame();

		// ESCキーが押されたらループを抜ける
		if (PressKey(DIK_ESCAPE)) {
			break;
		}
	}

	// ライブラリの終了
	Novice::Finalize();
	return 0;
}