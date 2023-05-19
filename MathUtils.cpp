#include "MathUtils.h"
#include <assert.h>
#include <cmath>
#include <Novice.h>

Matrix4x4 Inverse(const Matrix4x4& m) {
	float A = (m.m[0][0] * m.m[1][1] * m.m[2][2] * m.m[3][3]) +
	          (m.m[0][0] * m.m[1][2] * m.m[2][3] * m.m[3][1]) +
	          (m.m[0][0] * m.m[1][3] * m.m[2][1] * m.m[3][2]) -
	          (m.m[0][0] * m.m[1][3] * m.m[2][2] * m.m[3][1]) -
	          (m.m[0][0] * m.m[1][2] * m.m[2][1] * m.m[3][3]) -
	          (m.m[0][0] * m.m[1][1] * m.m[2][3] * m.m[3][2]) -
	          (m.m[0][1] * m.m[1][0] * m.m[2][2] * m.m[3][3]) -
	          (m.m[0][2] * m.m[1][0] * m.m[2][3] * m.m[3][1]) -
	          (m.m[0][3] * m.m[1][0] * m.m[2][1] * m.m[3][2]) +
	          (m.m[0][3] * m.m[1][0] * m.m[2][2] * m.m[3][1]) +
	          (m.m[0][2] * m.m[1][0] * m.m[2][1] * m.m[3][3]) +
	          (m.m[0][1] * m.m[1][0] * m.m[2][3] * m.m[3][2]) +
	          (m.m[0][1] * m.m[1][2] * m.m[2][0] * m.m[3][3]) +
	          (m.m[0][2] * m.m[1][3] * m.m[2][0] * m.m[3][1]) +
	          (m.m[0][3] * m.m[1][1] * m.m[2][0] * m.m[3][2]) -
	          (m.m[0][3] * m.m[1][2] * m.m[2][0] * m.m[3][1]) -
	          (m.m[0][2] * m.m[1][1] * m.m[2][0] * m.m[3][3]) -
	          (m.m[0][1] * m.m[1][3] * m.m[2][0] * m.m[3][2]) -
	          (m.m[0][1] * m.m[1][2] * m.m[2][3] * m.m[3][0]) -
	          (m.m[0][2] * m.m[1][3] * m.m[2][1] * m.m[3][0]) -
	          (m.m[0][3] * m.m[1][1] * m.m[2][2] * m.m[3][0]) +
	          (m.m[0][3] * m.m[1][2] * m.m[2][1] * m.m[3][0]) +
	          (m.m[0][2] * m.m[1][1] * m.m[2][3] * m.m[3][0]) +
	          (m.m[0][1] * m.m[1][3] * m.m[2][2] * m.m[3][0]);

	Matrix4x4 result = MakeIdentity4x4();

	result.m[0][0] = 1 / A *
	                 ((m.m[1][1] * m.m[2][2] * m.m[3][3]) + (m.m[1][2] * m.m[2][3] * m.m[3][1]) +
	                  (m.m[1][3] * m.m[2][1] * m.m[3][2]) - (m.m[1][3] * m.m[2][2] * m.m[3][1]) -
	                  (m.m[1][2] * m.m[2][1] * m.m[3][3]) - (m.m[1][1] * m.m[2][3] * m.m[3][2]));

	result.m[0][1] = 1 / A *
	                 (-(m.m[0][1] * m.m[2][2] * m.m[3][3]) - (m.m[0][2] * m.m[2][3] * m.m[3][1]) -
	                  (m.m[0][3] * m.m[2][1] * m.m[3][2]) + (m.m[0][3] * m.m[2][2] * m.m[3][1]) +
	                  (m.m[0][2] * m.m[2][1] * m.m[3][3]) + (m.m[0][1] * m.m[2][3] * m.m[3][2]));

	result.m[0][2] = 1 / A *
	                 ((m.m[0][1] * m.m[1][2] * m.m[3][3]) + (m.m[0][2] * m.m[1][3] * m.m[3][1]) +
	                  (m.m[0][3] * m.m[1][1] * m.m[3][2]) - (m.m[0][3] * m.m[1][2] * m.m[3][1]) -
	                  (m.m[0][2] * m.m[1][1] * m.m[3][3]) - (m.m[0][1] * m.m[1][3] * m.m[3][2]));

	result.m[0][3] = 1 / A *
	                 (-(m.m[0][1] * m.m[1][2] * m.m[2][3]) - (m.m[0][2] * m.m[1][3] * m.m[2][1]) -
	                  (m.m[0][3] * m.m[1][1] * m.m[2][2]) + (m.m[0][3] * m.m[1][2] * m.m[2][1]) +
	                  (m.m[0][2] * m.m[1][1] * m.m[2][3]) + (m.m[0][1] * m.m[1][3] * m.m[2][2]));

	result.m[1][0] = 1 / A *
	                 (-(m.m[1][0] * m.m[2][2] * m.m[3][3]) - (m.m[1][2] * m.m[2][3] * m.m[3][0]) -
	                  (m.m[1][3] * m.m[2][0] * m.m[3][2]) + (m.m[1][3] * m.m[2][2] * m.m[3][0]) +
	                  (m.m[1][2] * m.m[2][0] * m.m[3][3]) + (m.m[1][0] * m.m[2][3] * m.m[3][2]));

	result.m[1][1] = 1 / A *
	                 ((m.m[0][0] * m.m[2][2] * m.m[3][3]) + (m.m[0][2] * m.m[2][3] * m.m[3][0]) +
	                  (m.m[0][3] * m.m[2][0] * m.m[3][2]) - (m.m[0][3] * m.m[2][2] * m.m[3][0]) -
	                  (m.m[0][2] * m.m[2][0] * m.m[3][3]) - (m.m[0][0] * m.m[2][3] * m.m[3][2]));

	result.m[1][2] = 1 / A *
	                 (-(m.m[0][0] * m.m[1][2] * m.m[3][3]) - (m.m[0][2] * m.m[1][3] * m.m[3][0]) -
	                  (m.m[0][3] * m.m[1][0] * m.m[3][2]) + (m.m[0][3] * m.m[1][2] * m.m[3][0]) +
	                  (m.m[0][2] * m.m[1][0] * m.m[3][3]) + (m.m[0][0] * m.m[1][3] * m.m[3][2]));

	result.m[1][3] = 1 / A *
	                 ((m.m[0][0] * m.m[1][2] * m.m[2][3]) + (m.m[0][2] * m.m[1][3] * m.m[2][0]) +
	                  (m.m[0][3] * m.m[1][0] * m.m[2][2]) - (m.m[0][3] * m.m[1][2] * m.m[2][0]) -
	                  (m.m[0][2] * m.m[1][0] * m.m[2][3]) - (m.m[0][0] * m.m[1][3] * m.m[2][2]));

	result.m[2][0] = 1 / A *
	                 ((m.m[1][0] * m.m[2][1] * m.m[3][3]) + (m.m[1][1] * m.m[2][3] * m.m[3][0]) +
	                  (m.m[1][3] * m.m[2][0] * m.m[3][1]) - (m.m[1][3] * m.m[2][1] * m.m[3][0]) -
	                  (m.m[1][1] * m.m[2][0] * m.m[3][3]) - (m.m[1][0] * m.m[2][3] * m.m[3][1]));

	result.m[2][1] = 1 / A *
	                 (-(m.m[0][0] * m.m[2][1] * m.m[3][3]) - (m.m[0][1] * m.m[2][3] * m.m[3][0]) -
	                  (m.m[0][3] * m.m[2][0] * m.m[3][1]) + (m.m[0][3] * m.m[2][1] * m.m[3][0]) +
	                  (m.m[0][1] * m.m[2][0] * m.m[3][3]) + (m.m[0][0] * m.m[2][3] * m.m[3][1]));

	result.m[2][2] = 1 / A *
	                 ((m.m[0][0] * m.m[1][1] * m.m[3][3]) + (m.m[0][1] * m.m[1][3] * m.m[3][0]) +
	                  (m.m[0][3] * m.m[1][0] * m.m[3][1]) - (m.m[0][3] * m.m[1][1] * m.m[3][0]) -
	                  (m.m[0][1] * m.m[1][0] * m.m[3][3]) - (m.m[0][0] * m.m[1][3] * m.m[3][1]));

	result.m[2][3] = 1 / A *
	                 (-(m.m[0][0] * m.m[1][1] * m.m[2][3]) - (m.m[0][1] * m.m[1][3] * m.m[2][0]) -
	                  (m.m[0][3] * m.m[1][0] * m.m[2][1]) + (m.m[0][3] * m.m[1][1] * m.m[2][0]) +
	                  (m.m[0][1] * m.m[1][0] * m.m[2][3]) + (m.m[0][0] * m.m[1][3] * m.m[2][1]));

	result.m[3][0] = 1 / A *
	                 (-(m.m[1][0] * m.m[2][1] * m.m[3][2]) - (m.m[1][1] * m.m[2][2] * m.m[3][0]) -
	                  (m.m[1][2] * m.m[2][0] * m.m[3][1]) + (m.m[1][2] * m.m[2][1] * m.m[3][0]) +
	                  (m.m[1][1] * m.m[2][0] * m.m[3][2]) + (m.m[1][0] * m.m[2][2] * m.m[3][1]));

	result.m[3][1] = 1 / A *
	                 ((m.m[0][0] * m.m[2][1] * m.m[3][2]) + (m.m[0][1] * m.m[2][2] * m.m[3][0]) +
	                  (m.m[0][2] * m.m[2][0] * m.m[3][1]) - (m.m[0][2] * m.m[2][1] * m.m[3][0]) -
	                  (m.m[0][1] * m.m[2][0] * m.m[3][2]) - (m.m[0][0] * m.m[2][2] * m.m[3][1]));

	result.m[3][2] = 1 / A *
	                 (-(m.m[0][0] * m.m[1][1] * m.m[3][2]) - (m.m[0][1] * m.m[1][2] * m.m[3][0]) -
	                  (m.m[0][2] * m.m[1][0] * m.m[3][1]) + (m.m[0][2] * m.m[1][1] * m.m[3][0]) +
	                  (m.m[0][1] * m.m[1][0] * m.m[3][2]) + (m.m[0][0] * m.m[1][2] * m.m[3][1]));

	result.m[3][3] = 1 / A *
	                 ((m.m[0][0] * m.m[1][1] * m.m[2][2]) + (m.m[0][1] * m.m[1][2] * m.m[2][0]) +
	                  (m.m[0][2] * m.m[1][0] * m.m[2][1]) - (m.m[0][2] * m.m[1][1] * m.m[2][0]) -
	                  (m.m[0][1] * m.m[1][0] * m.m[2][2]) - (m.m[0][0] * m.m[1][2] * m.m[2][1]));

	return result;
}

Matrix4x4 MakeAffineMatrix(const Vector3& scale, const Vector3& rotate, const Vector3& translate) {
	Matrix4x4 result = MakeIdentity4x4();
	Matrix4x4 scaleMatrix = MakeScaleMatrix(scale);
	Matrix4x4 rotateXMatrix = MakeRotateXMatrix(rotate.x);
	Matrix4x4 rotateYMatrix = MakeRotateYMatrix(rotate.y);
	Matrix4x4 rotateZMatrix = MakeRotateZMatrix(rotate.z);
	Matrix4x4 rotateXYZMatrix = Multiply(rotateXMatrix, Multiply(rotateYMatrix, rotateZMatrix));
	Matrix4x4 translateMatrix = MakeTranslateMatrix(translate);
	result = Multiply(scaleMatrix, Multiply(rotateXYZMatrix, translateMatrix));
	return result;
}

void DrawGrid(const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{
	const float kGridHalfWidth = 2.0f;
	const uint32_t kSubdivision = 10;
	const float kGridEvery = (kGridHalfWidth * 2.0f) / float(kSubdivision);

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		Vector3 startGrid = Vector3{ kGridHalfWidth,0,-kGridHalfWidth + (kGridEvery * xIndex) };
		Vector3 endGrid = Vector3{ -kGridHalfWidth,0,-kGridHalfWidth + (kGridEvery * xIndex)};

		Vector3 ncdStartGrid = Transform(startGrid, viewProjectionMatrix);
		Vector3 screenStartGrid = Transform(ncdStartGrid, viewportMatrix);

		Vector3 ncdEndGrid = Transform(endGrid, viewProjectionMatrix);
		Vector3 screenEndGrid = Transform(ncdEndGrid, viewportMatrix);

		Novice::DrawLine(int(screenStartGrid.x), int(screenStartGrid.y), int(screenEndGrid.x), int(screenEndGrid.y), GREEN);
			
	}

	for (uint32_t xIndex = 0; xIndex <= kSubdivision; ++xIndex) {
		Vector3 startGrid = Vector3{ -kGridHalfWidth + (kGridEvery * xIndex),0,kGridHalfWidth};
		Vector3 endGrid = Vector3{ -kGridHalfWidth + (kGridEvery * xIndex),0,-kGridHalfWidth};

		Vector3 ncdStartGrid = Transform(startGrid, viewProjectionMatrix);
		Vector3 screenStartGrid = Transform(ncdStartGrid, viewportMatrix);

		Vector3 ncdEndGrid = Transform(endGrid, viewProjectionMatrix);
		Vector3 screenEndGrid = Transform(ncdEndGrid, viewportMatrix);

		Novice::DrawLine(int(screenStartGrid.x), int(screenStartGrid.y), int(screenEndGrid.x), int(screenEndGrid.y), GREEN);

	}

}

void DrawSphere(const Sphere& sphere, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	const uint32_t kSubdivision = 20;
	const float kLonEvery = (360 / kSubdivision) * ((float)M_PI / 180);
	const float kLatEvery = (360 / kSubdivision) * ((float)M_PI / 180);

	const float theta = (float)M_PI / kSubdivision;
	const float phi = (2 * (float)M_PI) / kSubdivision;

	for (uint32_t latIndex = 0; latIndex < kSubdivision; ++latIndex) {
		float lat = -(float)M_PI / 2.0f + kLatEvery * latIndex;

		for (uint32_t lonIndex = 0; lonIndex < kSubdivision; ++lonIndex) {
			float lon = lonIndex * kLonEvery;
			Vector3 a, b, c;
			a = sphere.radius * Vector3{ std::cos(lat) * std::cos(lon),std::sin(lat),std::cos(lat) * std::sin(lon) };
			b = sphere.radius * Vector3{ std::cos(lat + theta) * std::cos(lon),std::sin(lat + theta),std::cos(lat + theta) * std::sin(lon) };
			c = sphere.radius * Vector3{ std::cos(lat) * std::cos(lon + phi),std::sin(lat),std::cos(lat) * std::sin(lon + phi) };

			Vector3 ncdA, ncdB, ncdC;
			ncdA = Transform(a, viewProjectionMatrix);
			ncdB = Transform(b, viewProjectionMatrix);
			ncdC = Transform(c, viewProjectionMatrix);

			Vector3 screenA, screenB, screenC;
			screenA = Transform(ncdA, viewportMatrix);
			screenB = Transform(ncdB, viewportMatrix);
			screenC = Transform(ncdC, viewportMatrix);

			Novice::DrawLine((int)screenA.x, (int)screenA.y, (int)screenB.x, (int)screenB.y, color);
			Novice::DrawLine((int)screenA.x, (int)screenA.y, (int)screenC.x, (int)screenC.y, color);

		}



	}


}
