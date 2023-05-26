#include "Collision.h"

bool IsCollision(const Sphere& s1, const Sphere& s2)
{
    if (Length(Subtract(s2.center, s1.center)) < s1.radius + s2.radius) {
        return true;
    }

    return false;

}

bool IsCollision(const Sphere& sphere, const Plane& plane)
{
    float length = std::abs(Dot(plane.normal, sphere.center) - plane.distance);
    if (length < sphere.radius) {
        return true;
    }

    return false;
}
