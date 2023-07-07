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

Vector3 PositionToScreen(const Vector3& pos, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix)
{

	Vector3 ncdPos = Transform(pos, viewProjectionMatrix);
	Vector3 screenPos = Transform(ncdPos, viewportMatrix);
	return screenPos;

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
			a = sphere.center + (sphere.radius * Vector3{ std::cos(lat) * std::cos(lon),std::sin(lat),std::cos(lat) * std::sin(lon) });
			b = sphere.center + (sphere.radius * Vector3{ std::cos(lat + theta) * std::cos(lon),std::sin(lat + theta),std::cos(lat + theta) * std::sin(lon) });
			c = sphere.center + (sphere.radius * Vector3{ std::cos(lat) * std::cos(lon + phi),std::sin(lat),std::cos(lat) * std::sin(lon + phi) });

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

void DrawPlane(const Plane& plane, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 center = plane.distance * plane.normal;
	Vector3 perpendiculars[4];
	perpendiculars[0] = Normalize(Perpendicular(plane.normal));
	perpendiculars[1] = { -perpendiculars[0].x,-perpendiculars[0].y,-perpendiculars[0].z };
	perpendiculars[2] = Cross(plane.normal, perpendiculars[0]);
	perpendiculars[3] = { -perpendiculars[2].x,-perpendiculars[2].y,-perpendiculars[2].z };

	Vector3 points[4];

	for (uint32_t index = 0; index < 4; ++index) {
		Vector3 extend = 2.0f * perpendiculars[index];
		Vector3 point = center + extend;
		points[index] = Transform(Transform(point, viewProjectionMatrix), viewportMatrix);
	}

	Novice::DrawLine((int)points[0].x, (int)points[0].y, (int)points[2].x, (int)points[2].y, color);
	Novice::DrawLine((int)points[2].x, (int)points[2].y, (int)points[1].x, (int)points[1].y, color);
	Novice::DrawLine((int)points[1].x, (int)points[1].y, (int)points[3].x, (int)points[3].y, color);
	Novice::DrawLine((int)points[3].x, (int)points[3].y, (int)points[0].x, (int)points[0].y, color);

}

void DrawSegment(const Segment& segment, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{

	Vector3 ncdA = Transform(segment.origin, viewProjectionMatrix);
	Vector3 ncdB = Transform(segment.origin + segment.diff, viewProjectionMatrix);

	Vector3 screenA = Transform(ncdA, viewportMatrix);
	Vector3 screenB = Transform(ncdB, viewportMatrix);

	Novice::DrawLine((int)screenA.x, (int)screenA.y, (int)screenB.x, (int)screenB.y, color);

}

void DrawTriangle(const Triangle& triangle, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{

	Vector3 ncdVertices0 = Transform(triangle.vertices[0], viewProjectionMatrix);
	Vector3 ncdVertices1 = Transform(triangle.vertices[1], viewProjectionMatrix);
	Vector3 ncdVertices2 = Transform(triangle.vertices[2], viewProjectionMatrix);

	Vector3 screenVertices0 = Transform(ncdVertices0, viewportMatrix);
	Vector3 screenVertices1 = Transform(ncdVertices1, viewportMatrix);
	Vector3 screenVertices2 = Transform(ncdVertices2, viewportMatrix);

	Novice::DrawTriangle((int)screenVertices0.x, (int)screenVertices0.y, (int)screenVertices1.x, (int)screenVertices1.y, (int)screenVertices2.x, (int)screenVertices2.y, color, kFillModeWireFrame);

}

void DrawAABB(const AABB& aabb, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	Vector3 vertices[8];
	Vector3 ncdVertices[8];
	Vector3 screenVertices[8];

	vertices[0] = { aabb.min.x,aabb.max.y,aabb.min.z };
	vertices[1] = { aabb.max.x,aabb.max.y,aabb.min.z };
	vertices[2] = { aabb.max.x,aabb.min.y,aabb.min.z };
	vertices[3] = { aabb.min.x,aabb.min.y,aabb.min.z };
	vertices[4] = { aabb.min.x,aabb.max.y,aabb.max.z };
	vertices[5] = { aabb.max.x,aabb.max.y,aabb.max.z };
	vertices[6] = { aabb.max.x,aabb.min.y,aabb.max.z };
	vertices[7] = { aabb.min.x,aabb.min.y,aabb.max.z };

	ncdVertices[0] = Transform(vertices[0], viewProjectionMatrix);
	ncdVertices[1] = Transform(vertices[1], viewProjectionMatrix);
	ncdVertices[2] = Transform(vertices[2], viewProjectionMatrix);
	ncdVertices[3] = Transform(vertices[3], viewProjectionMatrix);
	ncdVertices[4] = Transform(vertices[4], viewProjectionMatrix);
	ncdVertices[5] = Transform(vertices[5], viewProjectionMatrix);
	ncdVertices[6] = Transform(vertices[6], viewProjectionMatrix);
	ncdVertices[7] = Transform(vertices[7], viewProjectionMatrix);

	screenVertices[0] = Transform(ncdVertices[0], viewportMatrix);
	screenVertices[1] = Transform(ncdVertices[1], viewportMatrix);
	screenVertices[2] = Transform(ncdVertices[2], viewportMatrix);
	screenVertices[3] = Transform(ncdVertices[3], viewportMatrix);
	screenVertices[4] = Transform(ncdVertices[4], viewportMatrix);
	screenVertices[5] = Transform(ncdVertices[5], viewportMatrix);
	screenVertices[6] = Transform(ncdVertices[6], viewportMatrix);
	screenVertices[7] = Transform(ncdVertices[7], viewportMatrix);

	Novice::DrawLine((int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[1].x, (int)screenVertices[1].y, color);
	Novice::DrawLine((int)screenVertices[1].x, (int)screenVertices[1].y, (int)screenVertices[2].x, (int)screenVertices[2].y, color);
	Novice::DrawLine((int)screenVertices[2].x, (int)screenVertices[2].y, (int)screenVertices[3].x, (int)screenVertices[3].y, color);
	Novice::DrawLine((int)screenVertices[3].x, (int)screenVertices[3].y, (int)screenVertices[0].x, (int)screenVertices[0].y, color);
	Novice::DrawLine((int)screenVertices[4].x, (int)screenVertices[4].y, (int)screenVertices[5].x, (int)screenVertices[5].y, color);
	Novice::DrawLine((int)screenVertices[5].x, (int)screenVertices[5].y, (int)screenVertices[6].x, (int)screenVertices[6].y, color);
	Novice::DrawLine((int)screenVertices[6].x, (int)screenVertices[6].y, (int)screenVertices[7].x, (int)screenVertices[7].y, color);
	Novice::DrawLine((int)screenVertices[7].x, (int)screenVertices[7].y, (int)screenVertices[4].x, (int)screenVertices[4].y, color);
	Novice::DrawLine((int)screenVertices[0].x, (int)screenVertices[0].y, (int)screenVertices[4].x, (int)screenVertices[4].y, color);
	Novice::DrawLine((int)screenVertices[1].x, (int)screenVertices[1].y, (int)screenVertices[5].x, (int)screenVertices[5].y, color);
	Novice::DrawLine((int)screenVertices[2].x, (int)screenVertices[2].y, (int)screenVertices[6].x, (int)screenVertices[6].y, color);
	Novice::DrawLine((int)screenVertices[3].x, (int)screenVertices[3].y, (int)screenVertices[7].x, (int)screenVertices[7].y, color);
}

void DrawBezier(const Vector3& controlPoint0, const Vector3& controlPoint1, const Vector3& controlPoint2, const Matrix4x4& viewProjectionMatrix, const Matrix4x4& viewportMatrix, uint32_t color)
{
	int division = 36;
	float t = 0;
	float segmentStep = 1.0f / (float)division;
	
	for (int i = 0; i < division; i++) {

		Vector3 p01 = Lerp(controlPoint0, controlPoint1,t);
		Vector3 p12 = Lerp(controlPoint1, controlPoint2, t);
		Vector3 start = Lerp(p01, p12, t);
		Vector3 eP01 = Lerp(controlPoint0, controlPoint1, t + segmentStep);
		Vector3 eP12 = Lerp(controlPoint1, controlPoint2, t + segmentStep);
		Vector3 end = Lerp(eP01, eP12, t + segmentStep);
		
		Vector3 ncdStart = Transform(start, viewProjectionMatrix);
		Vector3 ncdEnd = Transform(end, viewProjectionMatrix);
		Vector3 screenStart = Transform(ncdStart, viewportMatrix);
		Vector3 screenEnd = Transform(ncdEnd, viewportMatrix);

		Novice::DrawLine((int)screenStart.x, (int)screenStart.y, (int)screenEnd.x, (int)screenEnd.y, color);

		t += segmentStep;

	}

	Vector3 screenCP0 = PositionToScreen(controlPoint0, viewProjectionMatrix, viewportMatrix);
	Vector3 screenCP1 = PositionToScreen(controlPoint1, viewProjectionMatrix, viewportMatrix);
	Vector3 screenCP2 = PositionToScreen(controlPoint2, viewProjectionMatrix, viewportMatrix);

	Sphere sphere0 = {
		{controlPoint0},0.1f,
	};

	Sphere sphere1 = {
		{controlPoint1},0.1f,
	};

	Sphere sphere2 = {
		{controlPoint2},0.1f,
	};

	DrawSphere(sphere0, viewProjectionMatrix, viewportMatrix, BLACK);
	DrawSphere(sphere1, viewProjectionMatrix, viewportMatrix, BLACK);
	DrawSphere(sphere2, viewProjectionMatrix, viewportMatrix, BLACK);

}
