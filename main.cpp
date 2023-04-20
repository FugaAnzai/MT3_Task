#include <Novice.h>
#include "keyInput.h"
#include "Function.h"
#include "Vector3.h"
#include "Matrix4x4.h"

const char kWindowTitle[] = "LD2A_01_アンザイフウガ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 rotate(0.4f, 1.43f, -0.8f);
	Matrix4x4 rotateXMatrix = Matrix4x4::MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = Matrix4x4::MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = Matrix4x4::MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Matrix4x4::Multiply(rotateXMatrix, Matrix4x4::Multiply(rotateYMatrix, rotateZMatrix));

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

		Function::MatrixScreenPrintf(0, 0, rotateXMatrix, "rotateXMatrix");
		Function::MatrixScreenPrintf(0, kRowHeight * 5, rotateYMatrix, "rotateYMatrix");
		Function::MatrixScreenPrintf(0, kRowHeight * 5 * 2, rotateZMatrix, "rotateZMatrix");
		Function::MatrixScreenPrintf(0, kRowHeight * 5 * 3, rotateXYZMatrix, "rotateXYZMatrix");

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