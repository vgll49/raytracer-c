#include "raylib.h"
#include "vec3.h"
#include <stdio.h>





int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 450;

    Vec3 a = {2, 4, 2};
    Vec3 b = {1, 1, 1};

    Vec3 c = vec3_sub(a, b);
    Vec3 a_norm = vec3_normalize(a);
    Vec3 cross = vec3_cross(a, b);
    float a_cross = vec3_dot(a, cross);
    float l_norm = vec3_length(a_norm);
    printf("x: %.4f, y: %.4f, z %.4f\n", c.x, c.y, c.z);
    printf("After Normalize: x: %.4f, y: %.4f, z %.4f\n", a_norm.x, a_norm.y, a_norm.z);
    printf("cross: x: %.4f, y: %.4f, z %.1f\n", cross.x, cross.y, cross.z);
    printf("dot a and cross is %.4f\n", a_cross);
    printf("lenght of a is: %.4f\n", vec3_length(a));
    printf("lenght of b is: %.4f\n", vec3_length(b));
    printf("l_norm %.4f\n", l_norm);
    printf("%.2f", sqrtf(0));
    printf("%.4f", 1.0f/0.0f);
    printf("%.4f", 0.0f/0.0f);
    

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