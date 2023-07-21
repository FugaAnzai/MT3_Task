#include <Novice.h>
#include "keyInput.h"
#include "Function.h"
#include "MathUtils.h"
#include "WinApp.h"
#include "ImGuiManager.h"
#include "Collision.h"
#include "PhysicsUtils.h"

const char kWindowTitle[] = "LD2A_01_アンザイフウガ";

// Windowsアプリでのエントリーポイント(main関数)
int WINAPI WinMain(HINSTANCE, HINSTANCE, LPSTR, int) {

	// ライブラリの初期化
	Novice::Initialize(kWindowTitle, 1280, 720);

	ConicalPendulum conicalPendulum;
	conicalPendulum.anchor = { 0.0f,1.0f,0.0f };
	conicalPendulum.length = 0.8f;
	conicalPendulum.halfApexAngle = 0.7f;
	conicalPendulum.angle = 0.0f;
	conicalPendulum.angularVelocity = 0.0f;

	Ball ball{};
	ball.position = { 5.8f,2.2f,0.0f };
	ball.mass = 2.0f;
	ball.radius = 0.05f;
	ball.color = BLUE;

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
		ImGuiIO io = ImGui::GetIO();
		if (ImGui::Button("Start")) {
			conicalPendulum.anchor = { 0.0f,1.0f,0.0f };
			conicalPendulum.length = 0.8f;
			conicalPendulum.halfApexAngle = 0.7f;
			conicalPendulum.angle = 0.0f;
			conicalPendulum.angularVelocity = 0.0f;
			ball.position = { 5.8f,2.2f,0.0f };
			ball.mass = 2.0f;
			ball.radius = 0.05f;
			ball.color = BLUE;

		}

		ImGui::End();

		ConicalPendulumSimulation(conicalPendulum, ball);

		Vector3 screenBallPos = PositionToScreen(ball.position, viewProjectionMatrix, viewportMatrix);
		Vector3 screenPendulumPos = PositionToScreen(conicalPendulum.anchor, viewProjectionMatrix, viewportMatrix);

		Sphere ballSphere{};
		ballSphere.center = ball.position;
		ballSphere.radius = 0.1f;

		///
		/// ↑更新処理ここまで
		///

		///
		/// ↓描画処理ここから
		///

		DrawGrid(viewProjectionMatrix, viewportMatrix);
		Novice::DrawLine((int)screenPendulumPos.x, (int)screenPendulumPos.y, (int)screenBallPos.x, (int)screenBallPos.y, WHITE);
		DrawSphere(ballSphere, viewProjectionMatrix, viewportMatrix,ball.color);

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