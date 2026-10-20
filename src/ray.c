#include "ray.h"

// t is the pos of a point along the ray
Color3 ray_at(CRay r, float t) {
    return vec3_add(r.origin, vec3_scale(r.direction, t));
}

// cast float to unsigned char and handle overflow
unsigned char f_scale_and_clamp_to_char(float f) {
    f *= 255;

    if(f > 255.0f) {
        return (unsigned char) 255;
    } else if(f < 0.0f) {
        return  (unsigned char) 0;
    } else {
        return (unsigned char) f;
    }
}

Color set_ray_color(Color3 ray_color) {
    // Convert linear light intensity to approximate gamma-2 display values.
    float r_gamma = ray_color.x > 0.0f ? sqrtf(ray_color.x) : 0.0f;
    float g_gamma = ray_color.y > 0.0f ? sqrtf(ray_color.y) : 0.0f;
    float b_gamma = ray_color.z > 0.0f ? sqrtf(ray_color.z) : 0.0f;

    unsigned char r = f_scale_and_clamp_to_char(r_gamma);
    unsigned char g = f_scale_and_clamp_to_char(g_gamma);
    unsigned char b = f_scale_and_clamp_to_char(b_gamma);

    return (Color){r, g, b, 255};

}
