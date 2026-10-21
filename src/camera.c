#include "camera.h"
#include "random.h"

#include <stdio.h>

#define RAY_T_MIN 0.001f

static Vec3 sample_square(void) {
    return (Vec3){
        (float)random_double_range(-0.5, 0.5),
        (float)random_double_range(-0.5, 0.5),
        0.0f
    };
}

static Point3 camera_defocus_disk_sample(const RTCamera *camera) {
    Vec3 disk_point = vec3_random_in_unit_disk();
    return vec3_add(camera->camera_center,
                    vec3_add(vec3_scale(camera->defocus_disk_u, disk_point.x),
                             vec3_scale(camera->defocus_disk_v, disk_point.y)));
}

static CRay camera_get_ray(const RTCamera *camera, int i, int j) {
    Vec3 offset = sample_square();
    Vec3 pixel_sample = vec3_add(
        camera->pixel00_location,
        vec3_add(
            vec3_scale(camera->pixel_delta_u, (float)i + offset.x),
            vec3_scale(camera->pixel_delta_v, (float)j + offset.y)
        )
    );

    Point3 ray_origin = camera->defocus_angle <= 0.0f
        ? camera->camera_center
        : camera_defocus_disk_sample(camera);
    return (CRay){ray_origin, vec3_sub(pixel_sample, ray_origin)};
}

void camera_init(RTCamera *camera){
    if (camera->samples_per_pixel < 1) camera->samples_per_pixel = 1;
    camera->image_height = (int)(camera->image_width/camera->aspect_ratio);
    if (camera->image_height < 1) camera->image_height = 1;

    float f_image_width = (float)camera->image_width;
    float f_image_height = (float)camera->image_height;

    camera->camera_center = camera->lookfrom;
    float focus_dist = camera->focus_dist;
    float theta = camera->vfov * (float)(acos(-1.0) / 180.0);
    float viewport_h = 2.0f * tanf(theta * 0.5f) * focus_dist;
    float viewport_w = viewport_h * (f_image_width / f_image_height);

    // Build an orthonormal coordinate frame for the camera.
    camera->camera_w = vec3_normalize(vec3_sub(camera->lookfrom, camera->lookat));
    camera->camera_u = vec3_normalize(vec3_cross(camera->vup, camera->camera_w));
    camera->camera_v = vec3_cross(camera->camera_w, camera->camera_u);

    Vec3 viewport_u = vec3_scale(camera->camera_u, viewport_w);
    Vec3 viewport_v = vec3_scale(camera->camera_v, -viewport_h);
    camera->pixel_delta_u = vec3_scale(viewport_u, 1.0f / f_image_width);
    camera->pixel_delta_v = vec3_scale(viewport_v, 1.0f / f_image_height);

    Vec3 viewport_center = vec3_sub(camera->camera_center,
                                    vec3_scale(camera->camera_w, focus_dist));
    Vec3 half_u = vec3_scale(viewport_u, 0.5f);
    Vec3 half_v = vec3_scale(viewport_v, 0.5f);

    // viewport top left 
    Vec3 camera_left = vec3_sub(viewport_center, vec3_add(half_u, half_v));

    // middle of the camera left pixel, used to calculate other pixel locations
    camera->pixel00_location =  vec3_add(vec3_add(camera_left, vec3_scale(camera->pixel_delta_u, 0.5f)),vec3_scale(camera->pixel_delta_v, 0.5f));

    float defocus_radius = focus_dist * tanf(
        camera->defocus_angle * (float)(acos(-1.0) / 360.0));
    camera->defocus_disk_u = vec3_scale(camera->camera_u, defocus_radius);
    camera->defocus_disk_v = vec3_scale(camera->camera_v, defocus_radius);
}

void camera_render(RTCamera *camera, const HittableList *world, Color *image_buffer) {
    if (camera->samples_per_pixel < 1) return;

    for (int j = 0; j < camera->image_height; j++) {
        fprintf(stderr, "\rScanlines remaining: %d ", camera->image_height - j);
        fflush(stderr);

        for(int i = 0; i < camera->image_width; i++) {
            Color3 pixel_color = {0.0f, 0.0f, 0.0f};
            for (int sample = 0; sample < camera->samples_per_pixel; sample++) {
                CRay ray = camera_get_ray(camera, i, j);
                pixel_color = vec3_add(pixel_color, calc_ray_color(ray, world, camera->max_depth));
            }

            float sample_scale = 1.0f / (float)camera->samples_per_pixel;
            pixel_color = vec3_scale(pixel_color, sample_scale);
            image_buffer[j * camera->image_width + i] = set_ray_color(pixel_color);
        }
    }

    fprintf(stderr, "\rDone.                 \n");
}

Color3 calc_ray_color(CRay r, const HittableList *world, int depth) {
    if (depth <= 0) return (Color3){0.0f, 0.0f, 0.0f};

    HitRecord record;
    // Ignore intersections extremely close to the origin to avoid re-hitting the surface
    // that produced a scattered ray (shadow acne)
    if (hittable_list_hit(world, r, RAY_T_MIN, INFINITY, &record)) {
        CRay scattered;
        Color3 attenuation;
        if (material_scatter(&record.material, r, record.point, record.normal, record.front_face,
                             &scattered, &attenuation)) {
            Color3 bounced_color = calc_ray_color(scattered, world, depth - 1);
            return vec3_mul(attenuation, bounced_color);
        }
        return (Color3){0.0f, 0.0f, 0.0f};
    }

    // not hit, blue/white sky coloration
    Vec3 norm_dir = vec3_normalize(r.direction);

    // 0 to 1
    float a = 0.5f * (norm_dir.y + 1.0f);

    // linear interpolation, both weights are always 1
    Vec3 white_part = vec3_scale((Vec3){1.0,1.0,1.0}, 1.0f-a);
    Vec3 blue_part = vec3_scale((Vec3){0.5, 0.7, 1.0}, a);
    return vec3_add(white_part, blue_part);
}
