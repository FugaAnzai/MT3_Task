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

	AABB aabb1 = {

		{-0.5f,-0.5f,-0.5f},
		{0.0f,0.0f,0.0f}

	};

	AABB aabb2 = {

		{0.2f,0.2f,0.2f},
		{1.0f,1.0f,1.0f}

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
		ImGui::SliderFloat3("position", &cameraPosition.x, -10, 10);
		ImGui::SliderFloat3("rotation", &cameraRotation.x, 0, 2 * (float)M_PI);
		ImGui::End();

		ImGui::Begin("aabb1");
		ImGui::SliderFloat3("min", &aabb1.min.x, -10, 10);
		ImGui::SliderFloat3("max", &aabb1.max.x, -10, 10);
		ImGui::End();

		aabb1.min.x = (std::min)(aabb1.min.x, aabb1.max.x);
		aabb1.max.x = (std::max)(aabb1.min.x, aabb1.max.x);
		aabb1.min.y = (std::min)(aabb1.min.y, aabb1.max.y);
		aabb1.max.y = (std::max)(aabb1.min.y, aabb1.max.y);
		aabb1.min.z = (std::min)(aabb1.min.z, aabb1.max.z);
		aabb1.max.z = (std::max)(aabb1.min.z, aabb1.max.z);

		aabb2.min.x = (std::min)(aabb2.min.x, aabb2.max.x);
		aabb2.max.x = (std::max)(aabb2.min.x, aabb2.max.x);
		aabb2.min.y = (std::min)(aabb2.min.y, aabb2.max.y);
		aabb2.max.y = (std::max)(aabb2.min.y, aabb2.max.y);
		aabb2.min.z = (std::min)(aabb2.min.z, aabb2.max.z);
		aabb2.max.z = (std::max)(aabb2.min.z, aabb2.max.z);

		ImGui::Begin("aabb2");
		ImGui::SliderFloat3("min", &aabb2.min.x, -10, 10);
		ImGui::SliderFloat3("max", &aabb2.max.x, -10, 10);
		ImGui::End();

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);

		if (IsCollision(aabb1, aabb2)) {
			DrawAABB(aabb1, viewProjectionMatrix, viewportMatrix, RED);
			DrawAABB(aabb2, viewProjectionMatrix, viewportMatrix, RED);
		}
		else {
			DrawAABB(aabb1, viewProjectionMatrix, viewportMatrix, WHITE);
			DrawAABB(aabb2, viewProjectionMatrix, viewportMatrix, WHITE);
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