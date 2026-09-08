#ifndef RTCAMERA_H
#define RTCAMERA_H

#include "vec3.h"
#include "ray.h"
#include "sphere.h"

typedef struct RTCamera {
    float aspect_ratio;  // Ratio of image width over height
    int image_width;// Rendered image width in pixel count
    int image_height; // Rendered image height
    Point3 camera_center; // camera center
    Point3 pixel00_location; // Location of pixel 0,0 used to calc other pixel locations
    Vec3 pixel_delta_u; // Offset to pixel to the right
    Vec3 pixel_delta_v; // Offset to pixel below

} RTCamera;

Color3 calc_ray_color(CRay r, Sphere s);
void camera_init(RTCamera *camera); // move init stuff here
void camera_render(RTCamera *camera, Sphere sp, Color *image_buffer); // move lmaioop in here, pass union of objects to render in here
#endif