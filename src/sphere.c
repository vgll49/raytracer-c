#include "sphere.h"

float hit_sphere(Sphere sphere, CRay ray) {
    float radius = sphere.radius;

    Vec3 oc = vec3_sub(sphere.center, ray.origin);
    float a = vec3_length_sq(ray.direction);
    float b = -2.0f * vec3_dot(ray.direction, oc);
    float c = vec3_length_sq(oc) - sphere.radius*radius;
    float discriminant = b*b - 4*a*c;

    if(discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant))/ (2.0*a);
    }
}