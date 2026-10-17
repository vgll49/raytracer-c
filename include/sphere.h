#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "ray.h"
#include <stdbool.h>

typedef struct Sphere {
    Vec3 center;
    float radius;
} Sphere;

bool sphere_hit(Sphere sphere, CRay ray, float t_min, float t_max, float *t, Point3 *point, Vec3 *outward_normal);

#endif
