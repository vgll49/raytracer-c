#include "raylib.h"
#include "sphere.h"
#include "camera.h"
#include "random.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_W 800//1200
#define SCREEN_H 450//675

void draw_scene(void *pixels, int width, int height);
int main(void) {
    srand((unsigned int)time(NULL));

    HittableList world;
    hittable_list_init(&world);
    RTMaterial ground = material_diffuse((Color3){0.5f, 0.5f, 0.5f});
    if (!hittable_list_add(&world,
            hittable_sphere((Sphere){(Vec3){0.0f, -1000.0f, 0.0f}, 1000.0f}, ground))) {
        hittable_list_destroy(&world);
        return 1;
    }

    const Point3 exclusion_center = {4.0f, 0.2f, 0.0f};
    for (int a = -11; a < 11; a++) {
        for (int b = -11; b < 11; b++) {
            double choose_material = random_double();
            Point3 center = {
                (float)a + 0.9f * (float)random_double(),
                0.2f,
                (float)b + 0.9f * (float)random_double()
            };

            if (vec3_length(vec3_sub(center, exclusion_center)) <= 0.9f) continue;

            RTMaterial material;
            if (choose_material < 0.8) {
                Color3 albedo = vec3_mul(vec3_random(), vec3_random());
                material = material_diffuse(albedo);
            } else if (choose_material < 0.95) {
                Color3 albedo = vec3_random_range(0.5f, 1.0f);
                float fuzz = (float)random_double_range(0.0, 0.5);
                material = material_metal(albedo, fuzz);
            } else {
                material = material_dielectric(1.5f);
            }

            if (!hittable_list_add(&world,
                    hittable_sphere((Sphere){center, 0.2f}, material))) {
                hittable_list_destroy(&world);
                return 1;
            }
        }
    }

    RTMaterial center_glass = material_dielectric(1.5f);
    RTMaterial left_diffuse = material_diffuse((Color3){0.4f, 0.2f, 0.1f});
    RTMaterial right_metal = material_metal((Color3){0.7f, 0.6f, 0.5f}, 0.0f);
    if (!hittable_list_add(&world, hittable_sphere((Sphere){(Vec3){0.0f, 1.0f, 0.0f}, 1.0f}, center_glass)) ||
        !hittable_list_add(&world, hittable_sphere((Sphere){(Vec3){-4.0f, 1.0f, 0.0f}, 1.0f}, left_diffuse)) ||
        !hittable_list_add(&world, hittable_sphere((Sphere){(Vec3){4.0f, 1.0f, 0.0f}, 1.0f}, right_metal))) {
        hittable_list_destroy(&world);
        return 1;
    }

    RTCamera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800; //1200;
    cam.samples_per_pixel = 5; //500;
    cam.max_depth = 50;
    cam.vfov = 20.0f;
    cam.lookfrom = (Point3){13.0f, 2.0f, 3.0f};
    cam.lookat = (Point3){0.0f, 0.0f, 0.0f};
    cam.vup = (Vec3){0.0f, 1.0f, 0.0f};
    cam.defocus_angle = 0.6f;
    cam.focus_dist = 10.0f;

    // init cam struct
    camera_init(&cam);

    size_t pixel_count = (size_t)cam.image_width * (size_t)cam.image_height;
    Color *image_buffer = malloc(pixel_count * sizeof(*image_buffer));
    if (image_buffer == NULL) {
        hittable_list_destroy(&world);
        return 1;
    }

    InitWindow(SCREEN_W, SCREEN_H, "raytracer");

    // RENDERING
    camera_render(&cam, &world, image_buffer);

    Image rendered_image = {
        .data = image_buffer,
        .width = cam.image_width,
        .height = cam.image_height,
        .mipmaps = 1,
        .format = PIXELFORMAT_UNCOMPRESSED_R8G8B8A8
    };
    if (!ExportImage(rendered_image, "images/final_render.jpg")) {
        fprintf(stderr, "Could not save images/final_render.jpg\n");
    } else {
        fprintf(stderr, "Saved images/final_render.jpg\n");
    }

    draw_scene(image_buffer, cam.image_width, cam.image_height);

    free(image_buffer);
    hittable_list_destroy(&world);
    return 0;
}

void draw_scene(void *pixels, int width, int height) {
    Image img = GenImageColor(width, height, PINK);
    Texture text = LoadTextureFromImage(img);
    UnloadImage(img);

    while (!WindowShouldClose())    
    {

        BeginDrawing(); 

            ClearBackground(RAYWHITE);
            UpdateTexture(text, pixels);
            DrawTexture(text, SCREEN_W/2-width/2, SCREEN_H/2-height/2, WHITE);
            
        EndDrawing();

    }

    UnloadTexture(text);
    CloseWindow();   
}
