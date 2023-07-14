#pragma once
#include "MathUtils.h"

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

void SpringSimulation(const Spring& spring,Ball& ball);

