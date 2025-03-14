#pragma once

#include "common.hpp"
#include "hittable.hpp"
class sphere : public hittable

{
public:
    sphere(const dpoint3 &center, double radius) : center(center), radius(std::fmax(0, radius)) {}

    bool hit(const ray &r, double ray_tmin, double ray_tmax, hit_record &rec) const override
    {
        dvec3 oc = center - r.origin();
        auto a = glm::dot(r.direction(), r.direction());
        // auto a = r.direction().length_squared();
        auto h = dot(r.direction(), oc);
        // auto c = oc.length_squared() - radius * radius;
        auto c = glm::dot(oc, oc) - radius * radius;

        auto discriminant = h * h - a * c;
        if (discriminant < 0)
            return false;

        auto sqrtd = std::sqrt(discriminant);

        // Find the nearest root that lies in the acceptable range.
        auto root = (h - sqrtd) / a;
        if (root <= ray_tmin || ray_tmax <= root)
        {
            root = (h + sqrtd) / a;
            if (root <= ray_tmin || ray_tmax <= root)
                return false;
        }

        rec.t = root;
        rec.p = r.at(rec.t);
        rec.normal = (rec.p - center) / radius;

        return true;
    }

private:
    dpoint3 center;
    double radius;
};