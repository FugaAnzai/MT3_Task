#include "Collision.h"

bool IsCollision(const Sphere& s1, const Sphere& s2)
{
    if (Length(Subtract(s2.center, s1.center)) < s1.radius + s2.radius) {
        return true;
    }

    return false;

}
