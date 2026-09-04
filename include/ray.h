#ifndef CRAY_H
#define CRAY_H

#include "vec3.h"
#include "raylib.h"

typedef struct CRay {
    Vec3 origin;
    Vec3 direction;
} CRay;


Color3 ray_at(CRay r, float t);
Color set_ray_color(Color3 ray_color);
unsigned char f_scale_and_clamp_to_char(float f);

#endif