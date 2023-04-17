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

	Matrix4x4 m1 = Matrix4x4(3.2f, 0.7f, 9.6f, 4.4f,
							5.5f, 1.3f, 7.8f, 2.1f, 
							6.9f, 8.0f, 2.6f, 1.0f, 
							0.5f, 7.2f, 5.1f, 3.3f);

	Matrix4x4 m2 = Matrix4x4(4.1f, 6.5f, 3.3f, 2.2f,
							8.8f, 0.6f, 9.9f, 7.7f,
							1.1f, 5.5f, 6.6f, 0.0f,
							3.3f, 9.9f, 8.8f, 2.2f);

	Matrix4x4 resultAdd = Matrix4x4::Add(m1, m2);
	Matrix4x4 resultSubtract = Matrix4x4::Subtract(m1, m2);
	Matrix4x4 resultMultiply = Matrix4x4::Multiply(m1, m2);
	Matrix4x4 resultInverseM1 = Matrix4x4::Inverse(m1);
	Matrix4x4 resultInverseM2 = Matrix4x4::Inverse(m2);
	Matrix4x4 resultTransposeM1 = Matrix4x4::Transpose(m1);
	Matrix4x4 resultTransposeM2 = Matrix4x4::Transpose(m2);
	Matrix4x4 identity = Matrix4x4::MakeIdentity4x4();

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

		Function::MatrixScreenPrintf(0, 0, resultAdd, "Add");
		Function::MatrixScreenPrintf(0, kRowHeight * 5, resultSubtract, "Subtract");
		Function::MatrixScreenPrintf(0, kRowHeight * 5 * 2, resultMultiply, "Multiply");
		Function::MatrixScreenPrintf(0, kRowHeight * 5 * 3, resultInverseM1, "InverseM1");
		Function::MatrixScreenPrintf(0, kRowHeight * 5 * 4, resultInverseM2, "InverseM2");
		Function::MatrixScreenPrintf(kColumnWidth * 5, 0, resultTransposeM1, "TransposeM1");
		Function::MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5, resultTransposeM2, "TransposeM2");
		Function::MatrixScreenPrintf(kColumnWidth * 5, kRowHeight * 5 * 2, identity, "Identity");

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