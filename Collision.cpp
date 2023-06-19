#include "Collision.h"
#include <algorithm>
#include <ImGuiManager.h>

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

bool IsCollision(const AABB& a, const AABB& b)
{
    if ((a.min.x <= b.max.x && a.max.x >= b.min.x) &&
        (a.min.y <= b.max.y && a.max.y >= b.min.y) &&
        (a.min.z <= b.max.z && a.max.z >= b.min.z)) {
        return true;
    }

    return false;
}

bool IsCollision(const AABB& aabb, const Sphere& sphere) {
    
    Vector3 closestPoint{ std::clamp(sphere.center.x,aabb.min.x,aabb.max.x),
        std::clamp(sphere.center.y,aabb.min.y,aabb.max.y),
        std::clamp(sphere.center.z,aabb.min.z,aabb.max.z)
    };

    float distance = Length(closestPoint - sphere.center);

    if (distance <= sphere.radius) {
        return true;
    }

    return false;
    
}

bool IsCollision(const AABB& aabb, const Segment& segment)
{
    float tXmin = (aabb.min.x - segment.origin.x) / segment.diff.x;
    float tXmax = (aabb.max.x - segment.origin.x) / segment.diff.x;
    float tYmin = (aabb.min.y - segment.origin.y) / segment.diff.y;
    float tYmax = (aabb.max.y - segment.origin.y) / segment.diff.y;
    float tZmin = (aabb.min.z - segment.origin.z) / segment.diff.z;
    float tZmax = (aabb.max.z - segment.origin.z) / segment.diff.z;

    float tNearX = (std::min)(tXmin, tXmax);
    float tFarX = (std::max)(tXmin, tXmax);
    float tNearY = (std::min)(tYmin, tYmax);
    float tFarY = (std::max)(tYmin, tYmax);
    float tNearZ = (std::min)(tZmin, tZmax);
    float tFarZ = (std::max)(tZmin, tZmax);

    float tmin = (std::max)((std::max)(tNearX, tNearY), tNearZ);
    float tmax = (std::min)((std::min)(tFarX, tFarY), tFarZ);

    ImGui::Begin("t");
    ImGui::InputFloat("tmin", &tmin);
    ImGui::InputFloat("tmax", &tmax);
    ImGui::End();

    if (tmin < tmax) {
        
        if((tmin > 1.0f && tmax > 1.0f) || (tmax < 0.0f && tmin < 0.0f)){return false;}
        return true;
    }

    return false;
}
