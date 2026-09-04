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
   
    unsigned char r =  f_scale_and_clamp_to_char(ray_color.x);
    unsigned char g =  f_scale_and_clamp_to_char(ray_color.y);
    unsigned char b =  f_scale_and_clamp_to_char(ray_color.z);

    return (Color){r, g, b, 255};

}