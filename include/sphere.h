#ifndef SPHERE_H
#define SPHERE_H

#include "vec3.h"
#include "ray.h"

typedef struct Sphere {
    Vec3 center;
    float radius;
} Sphere;


float hit_sphere(Sphere sphere, CRay ray);

#endif