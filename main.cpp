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

	Vector3 translate(4.1f, 2.6f, 0.8f);
	Vector3 scale(1.5f, 5.2f, 7.3f);
	Matrix4x4 translateMatrix = Matrix4x4::MakeTranslateMatrix(translate);
	Matrix4x4 scaleMatrix = Matrix4x4::MakeScaleMatrix(scale);
	Vector3 point(2.3f, 3.8f, 1.4f);
	Matrix4x4 transformMatrix(1.0f, 2.0f, 3.0f, 4.0f, 3.0f, 1.0f, 1.0f, 2.0f, 1.0f, 4.0f, 2.0f, 3.0f, 2.0f, 2.0f, 1.0f, 3.0f);

	Vector3 transformed = Vector3::Transform(point, transformMatrix);

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

		Function::Vector3ScreenPrintf(0, 0, transformed, "transformed");
		Function::MatrixScreenPrintf(0, kRowHeight, translateMatrix, "tranlateMatrix");
		Function::MatrixScreenPrintf(0, kRowHeight * 6, scaleMatrix, "scaleMatrix");
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