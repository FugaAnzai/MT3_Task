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

bool IsCollision(const Triangle& triangle, const Segment& segment)
{
    Vector3 v01 = triangle.vertices[1] - triangle.vertices[0];
    Vector3 v12 = triangle.vertices[2] - triangle.vertices[1];
    Vector3 v20 = triangle.vertices[0] - triangle.vertices[2];
    Plane plane;

    plane.normal = Cross(v01, v12);
    plane.distance = Dot(triangle.vertices[0], plane.normal);

    if (IsCollision(segment, plane)) {
        float dot = Dot(segment.diff, plane.normal);
        float t = (plane.distance - (Dot(segment.origin, plane.normal))) / dot;
        Vector3 p = segment.origin + (t * segment.diff);

        Vector3 v1p = p - triangle.vertices[1];
        Vector3 v2p = p - triangle.vertices[2];
        Vector3 v0p = p - triangle.vertices[0];

        Vector3 cross01 = Cross(v01, v1p);
        Vector3 cross12 = Cross(v12, v2p);
        Vector3 cross20 = Cross(v20, v0p);

        if (Dot(cross01, plane.normal) >= 0.0f &&
            Dot(cross12, plane.normal) >= 0.0f &&
            Dot(cross20, plane.normal) >= 0.0f) {
            return true;
        }

    }

    return false;
}
