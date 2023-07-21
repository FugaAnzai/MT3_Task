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

void CircleMotionSimulation(const float& angularVelocity, const float& radius, const Vector3& center, float& angle, Ball& ball)
{
	angle += angularVelocity * PhysicsUtils::deltaTime;

	ball.position.x = center.x + cosf(angle) * radius;
	ball.position.y = center.y + sinf(angle) * radius;
	ball.position.z = center.z;

}

void PendulumSimulation(Pendulum& pendulum, Ball& ball)
{
	pendulum.angularAcceleration = -(9.8f / pendulum.length) * std::sin(pendulum.angle);
	pendulum.angularVelocity += pendulum.angularAcceleration * PhysicsUtils::deltaTime;
	pendulum.angle += pendulum.angularVelocity * PhysicsUtils::deltaTime;

	ball.position.x = pendulum.anchor.x + std::sin(pendulum.angle) * pendulum.length;
	ball.position.y = pendulum.anchor.y - std::cos(pendulum.angle) * pendulum.length;
	ball.position.z = pendulum.anchor.z;

}
