#include "raylib.h"
#include "sphere.h"
#include "camera.h"
#include <stdlib.h>
#include <time.h>
#define SCREEN_W 800
#define SCREEN_H 450

void draw_scene(void *pixels, int width, int height);
int main(void) {
    srand((unsigned int)time(NULL));

    HittableList world;
    hittable_list_init(&world);
    RTMaterial ground = material_diffuse((Color3){0.8f, 0.8f, 0.0f});
    RTMaterial center = material_diffuse((Color3){0.1f, 0.2f, 0.5f});
    RTMaterial left_glass = material_dielectric(1.5f);
    RTMaterial inner_air = material_dielectric(1.0f / 1.5f);
    RTMaterial right_metal = material_metal((Color3){0.8f, 0.6f, 0.2f}, 0.0f);

    if (!hittable_list_add(&world, hittable_sphere((Sphere){(Vec3){0.0f,-100.5f,-1.0f}, 100.0f}, ground)) ||
        !hittable_list_add(&world, hittable_sphere((Sphere){(Vec3){0.0f,0.0f,-1.2f}, 0.5f}, center)) ||
        !hittable_list_add(&world, hittable_sphere((Sphere){(Vec3){-1.0f,0.0f,-1.0f}, 0.5f}, left_glass)) ||
        !hittable_list_add(&world, hittable_sphere((Sphere){(Vec3){-1.0f,0.0f,-1.0f}, 0.4f}, inner_air)) ||
        !hittable_list_add(&world, hittable_sphere((Sphere){(Vec3){1.0f,0.0f,-1.0f}, 0.5f}, right_metal))) {
        hittable_list_destroy(&world);
        return 1;
    }

    RTCamera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;
    cam.samples_per_pixel = 100;
    cam.max_depth = 50;

    // init cam struct
    camera_init(&cam);

    // create buffer TODO:: can get replaced with camera init + around 1,4mb on the stack
    Color image_buffer[cam.image_width*cam.image_height];

    InitWindow(SCREEN_W, SCREEN_H, "raytracer");

    // RENDERING
    camera_render(&cam, &world, image_buffer);

    draw_scene(image_buffer, cam.image_width, cam.image_height);

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
