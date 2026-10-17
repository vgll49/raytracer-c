#include "camera.h"

void camera_init(RTCamera *camera){
    
    camera->image_height = (int)(camera->image_width/camera->aspect_ratio);
    if (camera->image_height < 1) camera->image_height = 1;

    float f_image_width = (float)camera->image_width;
    float f_image_height = (float)camera->image_height;
    
    // Viewport dimensions
    float focal_l = 1.0; // distance between camera center and viewport
    float viewport_h = 2.0f;
    float viewport_w = viewport_h * (f_image_width/f_image_height);
    // orin of all scene rays
    camera->camera_center = (Point3){0,0,0};

    // Calculate the vector across the horizontal and down the vertical viewport edges
    Vec3 viewport_u = {viewport_w, 0, 0};
    Vec3 viewport_v = {0, -viewport_h, 0};
    
    // Calculate the horizontal and vertical delta vectors from pixel to pixel
    camera->pixel_delta_u = vec3_scale(viewport_u, 1.0f/f_image_width);
    camera->pixel_delta_v = vec3_scale(viewport_v, 1.0f/f_image_height);

    // calc camera left
    Vec3 viewport_center = vec3_sub(camera->camera_center, (Vec3){0,0, focal_l});
    Vec3 half_u = vec3_scale(viewport_u, 0.5f);
    Vec3 half_v = vec3_scale(viewport_v, 0.5f);

    // viewport top left 
    Vec3 camera_left = vec3_sub(viewport_center, vec3_add(half_u, half_v));

    // middle of the camera left pixel, used to calculate other pixel locations
    camera->pixel00_location =  vec3_add(vec3_add(camera_left, vec3_scale(camera->pixel_delta_u, 0.5f)),vec3_scale(camera->pixel_delta_v, 0.5f));
}

void camera_render(RTCamera *camera, const HittableList *world, Color *image_buffer) {
    for (int j = 0; j < camera->image_height; j++) {
        //printf("Lines remaining: %d\n", camera->image_height - j);

        for(int i = 0; i < camera->image_width; i++) {

            Vec3 pixel_center = vec3_add(camera->pixel00_location, vec3_add(vec3_scale(camera->pixel_delta_u, i),  vec3_scale(camera->pixel_delta_v, j)));

            // center - origin
            Vec3 ray_direction = vec3_sub(pixel_center, camera->camera_center);

            // ray from origin to direction
            CRay ray  = {camera->camera_center, ray_direction};
            
            // get color for every ray
            Color3 r_color = calc_ray_color(ray, world);
            
            // j as row, i as column multipled by buffer to select the row
            image_buffer[j*camera->image_width+(int)i] = set_ray_color(r_color);
        }
    }
}

Color3 calc_ray_color(CRay r, const HittableList *world) {
    HitRecord record;
    if (hittable_list_hit(world, r, 0.001f, INFINITY, &record)) {
        return vec3_scale(vec3_add(record.normal, (Vec3){1,1,1}), 0.5f);
    }

    // not hit, blue/white "sky" coloration
    Vec3 norm_dir = vec3_normalize(r.direction);

    // 0 to 1
    float a = 0.5f * (norm_dir.y + 1.0f);

    // linear interpolation, both weights are always 1
    Vec3 white_part = vec3_scale((Vec3){1.0,1.0,1.0}, 1.0f-a);
    Vec3 blue_part = vec3_scale((Vec3){0.5, 0.7, 1.0}, a);
    return vec3_add(white_part, blue_part);
}
