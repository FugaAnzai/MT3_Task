#include "PhysicsUtils.h"

void SpringSimulation(const Spring& spring, Ball& ball)
{
	float deltaTime = 1.0f / 60.0f;

	Vector3 diff = ball.position - spring.anchor;
	float length = Length(diff);
	if (length != 0.0f) {
		Vector3 direction = Normalize(diff);
		Vector3 restPosition = spring.anchor + direction * spring.naturalLength;
		Vector3 displacement = length * (ball.position - restPosition);
		Vector3 restoringForce = -spring.stiffness * displacement;
		Vector3 dampingForce = -spring.damping * ball.velocity;
		Vector3 force = restoringForce + dampingForce;
		ball.acceleration = force * (1 / ball.mass);
	}

	ball.velocity += ball.acceleration * deltaTime;
	ball.position += ball.velocity * deltaTime;



}
