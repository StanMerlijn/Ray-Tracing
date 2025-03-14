#pragma once
#include "common.hpp"

class ray
{
public:
    ray() {}
    ray(const dpoint3 &origin, const dpoint3 &direction)
        : orig(origin), dir(direction) {}

    const dpoint3 &origin() const { return orig; }
    const dpoint3 &direction() const { return dir; }

    dpoint3 at(double t) const
    {
        return orig + t * dir;
    }

private:
    dpoint3 orig;
    dvec3 dir;
};
