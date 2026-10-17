#include "sphere.h"

bool sphere_hit(Sphere sphere, CRay ray, float t_min, float t_max, float *t, Point3 *point, Vec3 *outward_normal) {
    if (sphere.radius <= 0.0f) return false;

    float radius = sphere.radius;

    Vec3 oc = vec3_sub(sphere.center, ray.origin);
    float a = vec3_length_sq(ray.direction); // t^2 (length^2 of ray direction)
    if (a <= EPS) return false;
    float h = vec3_dot(ray.direction, oc); // -2 d * (C-Q) (direction of ray relative to sphere)
    float c = vec3_length_sq(oc) - sphere.radius*radius; // dostance of ray start to sphere center ^2
    float discriminant = h*h - a*c; // discriminant of quadratic equation, h = d · (C - Q)

    if(discriminant < 0) {
        return false;
    }

    float square_root = sqrtf(discriminant);
    float root = (h - square_root) / a;
    if (root <= t_min || root >= t_max) {
        root = (h + square_root) / a;
        if (root <= t_min || root >= t_max) return false;
    }

    *t = root;
    *point = ray_at(ray, root);
    *outward_normal = vec3_scale(vec3_sub(*point, sphere.center), 1.0f / sphere.radius);
    return true;
}
