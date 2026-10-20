#ifndef RTCAMERA_H
#define RTCAMERA_H

#include "vec3.h"
#include "ray.h"
#include "hittable.h"

typedef struct RTCamera {
    float aspect_ratio;  // Ratio of image width over height
    int image_width;// Rendered image width in pixel count
    int image_height; // Rendered image height
    int samples_per_pixel; // Antialising sample size
    Point3 camera_center; // camera center
    Point3 pixel00_location; // Location of pixel 0,0 used to calc other pixel locations
    Vec3 pixel_delta_u; // Offset to pixel to the right
    Vec3 pixel_delta_v; // Offset to pixel below

} RTCamera;

Color3 calc_ray_color(CRay r, const HittableList *world);
void camera_init(RTCamera *camera); // move init stuff here
void camera_render(RTCamera *camera, const HittableList *world, Color *image_buffer);
#endif
