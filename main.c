#include "raylib.h"
#include "vec3.h"
#include <stdio.h>


#define SCREEN_W 800
#define SCREEN_H 450
#define BUFFER_W 800.0f
#define BUFFER_H 450.0f


typedef struct CRay {
    Vec3 origin;
    Vec3 direction;
} CRay;

// t is the pos of a point along the ray
Vec3 ray_at(CRay r, float t) {
    return vec3_add(r.origin, vec3_scale(r.direction, t));
}
/*
Calculate the ray from the “eye” through the pixel,
Determine which objects the ray intersects, and
Compute a color for the closest intersection point.
*/


int main(void) {
    
    // Camera 
    float viewport_h = 2.0f;
    float viewport_w = viewport_h * (BUFFER_W/BUFFER_H);
    float focal_l = 1.0;
    // orin of all scene rays
    Vec3 camera_center = {0,0,0};

    // Calculate 
    Vec3 viewport_u = {viewport_w, 0, 0};
    Vec3 viewport_v = {0, -viewport_h, 0};

    //Vec3 pixel_delta_u = vec3_scale(viewport_u, 1.0f/BUFFER_W);
    //Vec3 pixel_delta_v = vec3_scale(viewport_v, 1.0f/BUFFER_H);

    Vec3 camera_left = vec3_sub(camera_center, (Vec3){-BUFFER_W/2, BUFFER_H/2, focal_l});

    printf("viewport_w is %.4f\n", viewport_w);
    Color image_buffer[(int)BUFFER_H*(int)BUFFER_W];

    vec3_print(camera_center);
    vec3_print(camera_left);
    InitWindow(SCREEN_W, SCREEN_H, "raytracer");

    // genImage
    // LoadTextureFromImage
    // unload image
    // update text
    Image img = GenImageColor(BUFFER_W, BUFFER_H, PINK);
    Texture text = LoadTextureFromImage(img);
    UnloadImage(img);
    for (int j = 0; j < (int)BUFFER_H; j++) {
        printf("Lines remaining: %d\n", (int)BUFFER_H - j);


        for(int i = 0; i < (int)BUFFER_W; i++) {
            float r = (float)j / (BUFFER_H-1);
            float g = (float)i / (BUFFER_W-1);

            int ri = r * 255;
            int gi = g * 255;

            // j as row, i as column multipled by buffer to select the row
            image_buffer[j*(int)BUFFER_W+i] = (Color){.r = ri, .g = gi, .b = 0, .a = 255};
        }
    }
    while (!WindowShouldClose())    
    {

        BeginDrawing(); 

            ClearBackground(RAYWHITE);
            UpdateTexture(text, image_buffer);
            DrawTexture(text, SCREEN_W/2-BUFFER_W/2, SCREEN_H/2-BUFFER_H/2, WHITE);
            
        EndDrawing();


    }
    UnloadTexture(text);
    CloseWindow();        
    
    return 0;
}
