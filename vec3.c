
#include "vec3.h"

Vec3 vec3_add(Vec3 a, Vec3 b) {
    float x = a.x + b.x;
    float y = a.y + b.y;
    float z = a.z + b.z;

    return (Vec3) {x,y,z};
}

Vec3 vec3_sub(Vec3 a, Vec3 b) {
    float x = a.x - b.x;
    float y = a.y - b.y;
    float z = a.z - b.z;

    return (Vec3){x, y, z};
}

Vec3 vec3_scale(Vec3 a,  float scale) {
    float x = a.x * scale;
    float y = a.y * scale;
    float z = a.z * scale;
    
    return (Vec3) {x,y,z};
}


// lighting
float vec3_dot(Vec3 a, Vec3 b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}


// real distance
float vec3_length(Vec3 a) {
    return sqrtf(vec3_dot(a, a));
}

// comparing distances
float vec3_length_sq(Vec3 a) {
    return vec3_dot(a, a);
}


Vec3 vec3_normalize(Vec3 a) {
    float length = vec3_length(a);

    assert(length > EPS);

    return (Vec3){a.x/length, a.y/length, a.z/length};
}

Vec3 vec3_cross(Vec3 a, Vec3 b) {
    Vec3 cp = {
        .x = a.y*b.z - b.y*a.z,
        .y = a.z*b.x - b.z*a.x,
        .z = a.x*b.y - b.x*a.y,
    };

    return cp;
}

// coloration
Vec3 vec3_mul(Vec3 a, Vec3 b) {
    return (Vec3){a.x*b.x, a.y*b.y, a.z*b.z};
}
