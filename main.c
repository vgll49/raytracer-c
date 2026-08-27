#include "raylib.h"
#include "vec3.h"
#include <stdio.h>


#define SCREEN_W 800
#define SCREEN_H 450
#define BUFFER_W 400
#define BUFFER_H 225

int main(void) {

    Color image_buffer [BUFFER_H*BUFFER_W];

    InitWindow(SCREEN_W, SCREEN_H, "raytracer");

    // genImage
    // LoadTextureFromImage
    // unload image
    // update text
    Image img = GenImageColor(BUFFER_W, BUFFER_H, PINK);
    Texture text = LoadTextureFromImage(img);
    UnloadImage(img);
    for (int j = 0; j < BUFFER_H; j++) {
        printf("Lines remaining: %d\n", BUFFER_H - j);
        for(int i = 0; i < BUFFER_W; i++) {
            float r = (float)j / (BUFFER_H-1);
            float g = (float)i / (BUFFER_W-1);

            int ri = r * 255;
            int gi = g * 255;

            // j as row, i as column multipled by buffer to select the row
            image_buffer[j*BUFFER_W+i] = (Color){.r = ri, .g = gi, .b = 0, .a = 255};
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
