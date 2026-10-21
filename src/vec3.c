
#include "vec3.h"
#include "random.h"

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

Vec3 vec3_random(void) {
    return (Vec3){(float)random_double(), (float)random_double(), (float)random_double()};
}

Vec3 vec3_random_range(float min, float max) {
    return (Vec3){
        (float)random_double_range(min, max),
        (float)random_double_range(min, max),
        (float)random_double_range(min, max)
    };
}

Vec3 vec3_random_in_unit_sphere(void) {
    for (;;) {
        Vec3 point = vec3_random_range(-1.0f, 1.0f);
        float length_squared = vec3_length_sq(point);
        if (length_squared < 1.0f && length_squared > EPS) return point;
    }
}

Vec3 vec3_random_in_unit_disk(void) {
    for (;;) {
        Vec3 point = {
            (float)random_double_range(-1.0, 1.0),
            (float)random_double_range(-1.0, 1.0),
            0.0f
        };
        if (vec3_length_sq(point) < 1.0f) return point;
    }
}

Vec3 vec3_random_unit_vector(void) {
    return vec3_normalize(vec3_random_in_unit_sphere());
}

Vec3 vec3_random_on_hemisphere(Vec3 normal) {
    Vec3 direction = vec3_random_unit_vector();
    return vec3_dot(direction, normal) > 0.0f ? direction : vec3_scale(direction, -1.0f);
}

Vec3 vec3_reflect(Vec3 direction, Vec3 normal) {
    return vec3_sub(direction, vec3_scale(normal, 2.0f * vec3_dot(direction, normal)));
}

Vec3 vec3_refract(Vec3 unit_direction, Vec3 normal, float eta_ratio) {
    float cos_theta = fminf(vec3_dot(vec3_scale(unit_direction, -1.0f), normal), 1.0f);
    Vec3 perpendicular = vec3_scale(
        vec3_add(unit_direction, vec3_scale(normal, cos_theta)), eta_ratio);
    float parallel_length = sqrtf(fabsf(1.0f - vec3_length_sq(perpendicular)));
    Vec3 parallel = vec3_scale(normal, -parallel_length);
    return vec3_add(perpendicular, parallel);
}

bool vec3_near_zero(Vec3 value) {
    return fabsf(value.x) < EPS && fabsf(value.y) < EPS && fabsf(value.z) < EPS;
}

// helper to print 
void vec3_print(Vec3 a) {
    printf("x: %.4f, y: %.4f, z: %.4f\n", a.x, a.y, a.z);
}
