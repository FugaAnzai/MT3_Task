#include "PhysicsUtils.h"

void GravitySimulation(Ball& ball)
{
	ball.velocity += PhysicsUtils::kGravity * PhysicsUtils::deltaTime;

}

void SpringSimulation(const Spring& spring, Ball& ball)
{

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

	GravitySimulation(ball);

	ball.velocity += ball.acceleration * PhysicsUtils::deltaTime;
	ball.position += ball.velocity * PhysicsUtils::deltaTime;



}
