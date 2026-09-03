#ifndef VEC3_H
#define VEC3_H


#include <math.h>
#define EPS 1e-8f
#include <assert.h>
#include <stdio.h>

typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

// typealias for coloration due to readability
typedef Vec3 Color3;

Vec3 vec3_add(Vec3 a, Vec3 b);
Vec3 vec3_sub(Vec3 a, Vec3 b);
Vec3 vec3_scale(Vec3 a,  float scale);
float vec3_dot(Vec3 a, Vec3 b);
float vec3_length(Vec3 a);
float vec3_length_sq(Vec3 a);
Vec3 vec3_normalize(Vec3 a);
Vec3 vec3_cross(Vec3 a, Vec3 b);
Vec3 vec3_mul(Vec3 a, Vec3 b);
void vec3_print(Vec3 a);
#endif