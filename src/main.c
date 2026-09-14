#include "raylib.h"
#include "sphere.h"
#include "camera.h"
#include <stdio.h>

#define SCREEN_W 800
#define SCREEN_H 450

void draw_scene(void *pixels, int width, int height);
// TODO: change to union of hittables, spheres for now
Sphere sp = {(Vec3){0,0,-1}, 0.5};

int main(void) {
    
    RTCamera cam;

    cam.aspect_ratio = 16.0 / 9.0;
    cam.image_width = 800;

    // init cam struct
    camera_init(&cam);

    // create buffer TODO:: can get replaced with camera init + around 1,4mb on the stack
    Color image_buffer[cam.image_width*cam.image_height];

    InitWindow(SCREEN_W, SCREEN_H, "raytracer");

    // RENDERING
    camera_render(&cam, sp, image_buffer);

    draw_scene(image_buffer, cam.image_width, cam.image_height);
     
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