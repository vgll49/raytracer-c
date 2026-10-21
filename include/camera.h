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
    int max_depth; // Maximum number of ray bounces
    float vfov; // Vertical field of view in degrees
    Point3 lookfrom; // Camera position
    Point3 lookat; // Point the camera looks at
    Vec3 vup; // Approximate world-up direction, controls camera roll
    float defocus_angle; // Defocus cone angle in degrees; 0 disables blur
    float focus_dist; // Distance to the plane in perfect focus
    Point3 camera_center; // camera center
    Point3 pixel00_location; // Location of pixel 0,0 used to calc other pixel locations
    Vec3 pixel_delta_u; // Offset to pixel to the right
    Vec3 pixel_delta_v; // Offset to pixel below
    Vec3 camera_u; // Camera-right basis vector
    Vec3 camera_v; // Camera-up basis vector
    Vec3 camera_w; // Opposite viewing direction basis vector
    Vec3 defocus_disk_u; // Horizontal radius vector for the lens disk
    Vec3 defocus_disk_v; // Vertical radius vector for the lens disk

} RTCamera;

Color3 calc_ray_color(CRay r, const HittableList *world, int depth);
void camera_init(RTCamera *camera); // move init stuff here
void camera_render(RTCamera *camera, const HittableList *world, Color *image_buffer);
#endif
