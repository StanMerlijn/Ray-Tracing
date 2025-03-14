#pragma once

#include "ray.hpp"

class hit_record
{
public:
    dpoint3 p;
    dvec3 normal;
    double t;
};

class hittable
{
public:
    virtual ~hittable() = default;

    virtual bool hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const = 0;
};