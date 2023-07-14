#include <Novice.h>
#include "keyInput.h"
#include "Function.h"
#include "MathUtils.h"
#include "WinApp.h"
#include "ImGuiManager.h"
#include "Collision.h"

const char kWindowTitle[] = "LD2A_01_アンザイフウガ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	Vector3 a{ 0.2f,1.0f,0.0f };
	Vector3 b{ 2.4f,3.1f,1.2f };
	Vector3 c = a + b;
	Vector3 d = a - b;
	Vector3 e = a * 2.4f;
	Vector3 rotate{ 0.4f,1.43f,-0.8f };
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateMatrix = rotateXMatrix * rotateYMatrix * rotateZMatrix;

	Vector3 cameraPosition{ 0.0f,1.0f,-5.0f };
	Vector3 cameraRotation{};


	// ウィンドウの×ボタンが押されるまでループ
	while (Novice::ProcessMessage() == 0) {
		// フレームの開始
		Novice::BeginFrame();

		// キー入力を受け取る
		CheckKey();

		///
		/// ↓更新処理ここから
		///

		Matrix4x4 cameraMatrix = MakeAffineMatrix({ 1.0f,1.0f,1.0f }, cameraRotation, cameraPosition);
		Matrix4x4 viewMatrix = Inverse(cameraMatrix);
		Matrix4x4 projectionMatrix = MakePerspectiveFovMatrix(3.141592f / 4, (float(WinApp::kWindowWidth) / float(WinApp::kWindowHeight)), 0.1f, 100.0f);
		Matrix4x4 viewProjectionMatrix = Multiply(viewMatrix, projectionMatrix);
		Matrix4x4 viewportMatrix = MakeViewportMatrix(0, 0, float(WinApp::kWindowWidth), float(WinApp::kWindowHeight), 0.0f, 1.0f);

		ImGui::Begin("Camera");
		ImGui::DragFloat3("position", &cameraPosition.x, 0.01f, -10, 10);
		ImGui::DragFloat3("rotation", &cameraRotation.x, 0.01f,(float) - M_PI, (float)M_PI);
		ImGui::End();

		ImGui::Begin("Window");
		ImGui::Text("c:%f,%f,%f", c.x, c.y, c.z);
		ImGui::Text("d:%f,%f,%f", d.x, d.y, d.z);
		ImGui::Text("e:%f,%f,%f", e.x, e.y, e.z);
		ImGui::Text("matrix:\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n%f,%f,%f,%f\n",
			rotateMatrix.m[0][0], rotateMatrix.m[0][1], rotateMatrix.m[0][2], rotateMatrix.m[0][3],
			rotateMatrix.m[1][0], rotateMatrix.m[1][1], rotateMatrix.m[1][2], rotateMatrix.m[1][3], 
			rotateMatrix.m[2][0], rotateMatrix.m[2][1], rotateMatrix.m[2][2], rotateMatrix.m[2][3], 
			rotateMatrix.m[3][0], rotateMatrix.m[3][1], rotateMatrix.m[3][2], rotateMatrix.m[3][3] );

		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

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