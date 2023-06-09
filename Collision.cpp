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

bool IsCollision(const Line& line, const Plane& plane)
{
    float dot = Dot(line.diff, plane.normal);

    if (dot == 0.0f) {
        return false;
    }

    //float t = (plane.distance - (Dot(line.origin, plane.normal))) / dot;

    return true;
}

bool IsCollision(const Ray& ray, const Plane& plane) {

    float dot = Dot(ray.diff, plane.normal);

    if (dot == 0.0f) {
        return false;
    }

    float t = (plane.distance - (Dot(ray.origin, plane.normal))) / dot;

    if (t >= 0) {
        return true;
    }

    return false;

}

bool IsCollision(const Segment& segment, const Plane& plane) {

    float dot = Dot(segment.diff, plane.normal);

    if (dot == 0.0f) {
        return false;
    }

    float t = (plane.distance - (Dot(segment.origin, plane.normal))) / dot;

    if (t >= 0 && t <= 1) {
        return true;
    }

    return false;
}
