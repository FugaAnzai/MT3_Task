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

	Sphere sphere1{Vector3(0,0,0),1.0f};
	Plane plane{ Vector3(0,1,0),0.5f };
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

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		ImGui::Begin("Camera");
		ImGui::SliderFloat3("position", &cameraPosition.x, -10, 10);
		ImGui::SliderFloat3("rotation", &cameraRotation.x, 0, 2 * (float)M_PI);
		ImGui::End();

		ImGui::Begin("sphere");
		ImGui::SliderFloat3("center", &sphere1.center.x, -10, 10);
		ImGui::SliderFloat("radius", &sphere1.radius, -10, 10);
		ImGui::End();

		ImGui::Begin("Plane");
		ImGui::DragFloat3("normal", &plane.normal.x, 0.01f);
		ImGui::End();

		plane.normal = Normalize(plane.normal);

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		if (IsCollision(sphere1, plane)) {
			DrawSphere(sphere1, viewProjectionMatrix, viewportMatrix, RED);
			DrawPlane(plane, viewProjectionMatrix, viewportMatrix, RED);
		}
		else {
			DrawSphere(sphere1, viewProjectionMatrix, viewportMatrix, WHITE);
			DrawPlane(plane, viewProjectionMatrix, viewportMatrix, WHITE);
		}
		

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