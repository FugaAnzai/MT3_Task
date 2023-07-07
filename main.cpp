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

	Vector3 scale[3] = {
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
		{1.0f,1.0f,1.0f},
	};

	Vector3 rotation[3] = {
	};

	Vector3 translation[3] = {
		{-0.8f,0.58f,1.0f},
		{1.76f,1.0f,-0.3f},
		{0.94f,-0.7f,2.3f},
	};

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

		ImGui::Begin("ControlPoint");
		ImGui::DragFloat3("scale0", &scale[0].x, 0.01f, -10, 10);
		ImGui::DragFloat3("scale1", &scale[1].x, 0.01f, -10, 10);
		ImGui::DragFloat3("scale2", &scale[2].x, 0.01f, -10, 10);
		ImGui::DragFloat3("rotation0", &rotation[0].x, 0.01f, -10, 10);
		ImGui::DragFloat3("rotation1", &rotation[1].x, 0.01f, -10, 10);
		ImGui::DragFloat3("rotation2", &rotation[2].x, 0.01f, -10, 10);
		ImGui::DragFloat3("translation0", &translation[0].x, 0.01f, -10, 10);
		ImGui::DragFloat3("translation1", &translation[1].x, 0.01f, -10, 10);
		ImGui::DragFloat3("translation2", &translation[2].x, 0.01f, -10, 10);
		ImGui::End();

		Vector3 shoulder = translation[0];
		Matrix4x4 shoulderMatrix = MakeAffineMatrix(Vector3{ scale[0] }, Vector3{ rotation[0] }, translation[0]);
		Vector3 elbow = translation[1] * shoulderMatrix;
		Matrix4x4 elbowMatrix = MakeAffineMatrix(Vector3{ scale[1] }, Vector3{ rotation[1] }, elbow);
		Vector3 hand = translation[2] * elbowMatrix;

		Sphere sphere0 = { {shoulder},0.3f, };
		Sphere sphere1 = { {elbow},0.3f, };
		Sphere sphere2 = { {hand},0.3f, };

		Vector3 screenCP0 = PositionToScreen(shoulder, viewProjectionMatrix, viewportMatrix);
		Vector3 screenCP1 = PositionToScreen(elbow, viewProjectionMatrix, viewportMatrix);
		Vector3 screenCP2 = PositionToScreen(hand, viewProjectionMatrix, viewportMatrix);

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);
		DrawSphere(sphere0, viewProjectionMatrix, viewportMatrix,RED);
		DrawSphere(sphere1, viewProjectionMatrix, viewportMatrix, GREEN);
		DrawSphere(sphere2, viewProjectionMatrix, viewportMatrix, BLUE);

		Novice::DrawLine((int)screenCP0.x, (int)screenCP0.y, (int)screenCP1.x, (int)screenCP1.y, WHITE);
		Novice::DrawLine((int)screenCP1.x, (int)screenCP1.y, (int)screenCP2.x, (int)screenCP2.y, WHITE);

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