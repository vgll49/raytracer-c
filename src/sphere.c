#include "sphere.h"

float hit_sphere(Sphere sphere, CRay ray) {
    float radius = sphere.radius;

    Vec3 oc = vec3_sub(sphere.center, ray.origin);
    float a = vec3_length_sq(ray.direction); // t^2 (length^2 of ray direction)
    float h = vec3_dot(ray.direction, oc); // -2 d * (C-Q) (direction of ray relative to sphere)
    float c = vec3_length_sq(oc) - sphere.radius*radius; // dostance of ray start to sphere center ^2
    float discriminant = h*h - a*c; // discriminant of quadratic equation, h = d · (C - Q)

    if(discriminant < 0) {
        return -1.0;
    } else {
        return (h - sqrt(discriminant))/ a;
    }
}