#include "raylib.h"
#include "vec3.h"
#include "ray.h"
#include "sphere.h"
#include "camera.h"
#include <stdio.h>

#define SCREEN_W 800
#define SCREEN_H 450

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
    Image img = GenImageColor(cam.image_width, cam.image_height, PINK);
    Texture text = LoadTextureFromImage(img);
    UnloadImage(img);

    // Render raytracer
    camera_render(&cam, sp, image_buffer);

    while (!WindowShouldClose())    
    {

        BeginDrawing(); 

            ClearBackground(RAYWHITE);
            UpdateTexture(text, image_buffer);
            DrawTexture(text, SCREEN_W/2-cam.image_width/2, SCREEN_H/2-cam.image_height/2, WHITE);
            
        EndDrawing();


    }
    UnloadTexture(text);
    CloseWindow();        
    
    return 0;
}
