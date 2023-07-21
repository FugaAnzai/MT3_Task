#pragma once
#include "MathUtils.h"

namespace PhysicsUtils {
	const float deltaTime = 1.0f / 60.0f;
	const Vector3 kGravity = { 0.0f,-9.8f,0.0f };
};

struct Ball
{
	Vector3 position;
	Vector3 velocity;
	Vector3 acceleration;
	float mass;
	float radius;
	unsigned int color;

};

struct Spring {
	Vector3 anchor; //固定された端
	float naturalLength; //自然長
	float stiffness; //剛性　ばね定数
	float damping;//減衰係数
};

void GravitySimulation(Ball& ball);
void SpringSimulation(const Spring& spring,Ball& ball);
void CircleMotionSimulation(const float& angularVelocity, const float& radius, const Vector3& center, float& angle, Ball& ball);

