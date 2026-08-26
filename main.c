#include "raylib.h"
#include <stdio.h>
#include <math.h>
typedef struct Vec3 {
    float x;
    float y;
    float z;
} Vec3;

Vec3 vec3_add(Vec3 a, Vec3 b) {
    float x = a.x + b.x;
    float y = a.y + b.y;
    float z = a.z + b.z;

    return (Vec3) {x,y,z};
}

Vec3 vec3_sub(Vec3 a, Vec3 b) {
    float x = a.x - b.x;
    float y = a.y - b.y;
    float z = a.z - b.z;

    return (Vec3){x, y, z};
}

Vec3 vec3_scale(Vec3 a,  float scale) {
    float x = a.x * scale;
    float y = a.y * scale;
    float z = a.z * scale;
    
    return (Vec3) {x,y,z}
}

float vec3_length(Vec3 a) {
    
    return sqrtf(a.x^2.0f+a.x^2+a.z^2);q
}

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    Vec3 a = {2, 4, 2};
    Vec3 b = {1, 1, 1};

    Vec3 c = vec3_sub(a, b);

    printf("x: %.1f, y: %.1f, z %.1f\n", c.x, c.y, c.z);

    InitWindow(screenWidth, screenHeight, "raytracer");



    while (!WindowShouldClose())    
    {

        BeginDrawing();
            ClearBackground(RAYWHITE);

        EndDrawing();


    }
    CloseWindow();        
    

    return 0;
}

/* 
funcs needed:
 vec3_scale, vec3_mul,
vec3_dot, vec3_cross,
vec3_length, vec3_length_sq, vec3_normalize

mul: . Komponentenweise Multiplikation zweier Vektoren — (a.x*b.x, a.y*b.y, a.z*b.z)
*/