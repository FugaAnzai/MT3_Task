#pragma once
#include "MathUtils.h"

bool IsCollision(const Sphere& s1, const Sphere& s2);
bool IsCollision(const Sphere& sphere, const Plane& plane);
bool IsCollision(const Line& line, const Plane& plane);
bool IsCollision(const Ray& ray, const Plane& plane);
bool IsCollision(const Segment& segment, const Plane& plane);
bool IsCollision(const Triangle& triangle, const Segment& segment);
bool IsCollision(const AABB& a, const AABB& b);
bool IsCollision(const AABB& aabb, const Sphere& sphere);
