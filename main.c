#include "raylib.h"
#include "vec3.h"
#include <stdio.h>


#define SCREEN_W 800
#define SCREEN_H 450
#define BUFFER_W 800.0f
#define BUFFER_H 450.0f
// #define BUFFER_Wf 800.0f
// #define BUFFER_Hf 450.0f

typedef struct CRay {
    Vec3 origin;
    Vec3 direction;
} CRay;


// t is the pos of a point along the ray
Color3 ray_at(CRay r, float t) {
    return vec3_add(r.origin, vec3_scale(r.direction, t));
}

float hit_sphere(Vec3 center, float radius, CRay ray) {
    Vec3 oc = vec3_sub(center, ray.origin);
    float a = vec3_length_sq(ray.direction);
    float b = -2.0f * vec3_dot(ray.direction, oc);
    float c = vec3_length_sq(oc) - radius*radius;
    float discriminant = b*b - 4*a*c;

    if(discriminant < 0) {
        return -1.0;
    } else {
        return (-b - sqrt(discriminant))/ (2.0*a);
    }
}

Color3 calc_ray_color(CRay r) {
    float t = hit_sphere((Vec3){0,0,-1}, 0.5, r);

    if (t > 0.0) {

        Vec3 N = vec3_normalize(vec3_sub(ray_at(r, t), (Vec3){0,0,-1}));
        return vec3_scale(vec3_add(N, (Vec3){1,1,1}), 0.5f);
    }

    Vec3 norm_dir = vec3_normalize(r.direction);

    // 0 to 1
    float a = 0.5f * (norm_dir.y + 1.0f);

    // linear interpolation, both weights are always 1
    Vec3 white_part = vec3_scale((Vec3){1.0,1.0,1.0}, 1.0f-a);
    Vec3 blue_part = vec3_scale((Vec3){0.5, 0.7, 1.0}, a);
    return vec3_add(white_part, blue_part);
}

// cast float to unsigned char and handle overflow
unsigned char f_scale_and_clamp_to_char(float f) {
    f *= 255;

    if(f > 255.0f) {
        return (unsigned char) 255;
    } else if(f < 0.0f) {
        return  (unsigned char) 0;
    } else {
        return (unsigned char) f;
    }
}

Color set_ray_color(Color3 ray_color) {
   


    unsigned char r =  f_scale_and_clamp_to_char(ray_color.x);
    unsigned char g =  f_scale_and_clamp_to_char(ray_color.y);
    unsigned char b =  f_scale_and_clamp_to_char(ray_color.z);

    return (Color){r, g, b, 255};

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

    Vec3 pixel_delta_u = vec3_scale(viewport_u, 1.0f/BUFFER_W);
    Vec3 pixel_delta_v = vec3_scale(viewport_v, 1.0f/BUFFER_H);


    // calc camera left
    Vec3 viewport_center = vec3_sub(camera_center, (Vec3){0,0, focal_l});
    Vec3 half_u = vec3_scale(viewport_u, 0.5f);
    Vec3 half_v = vec3_scale(viewport_v, 0.5f);
    Vec3 camera_left = vec3_sub(viewport_center, vec3_add(half_u, half_v));


    // middle of the camera left pixel, used to calculate other pixel locations
    Vec3 pixel00_location =  vec3_add(vec3_add(camera_left, vec3_scale(pixel_delta_u, 0.5f)),vec3_scale(pixel_delta_v, 0.5f));

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

            Vec3 pixel_center = vec3_add(pixel00_location, vec3_add(vec3_scale(pixel_delta_u, i),  vec3_scale(pixel_delta_v, j)));

            // center - origin
            Vec3 ray_direction = vec3_sub(pixel_center, camera_center);

            // ray from origin to direction
            CRay ray  = {camera_center, ray_direction};
            

            // debug
            if (i == 1 && j == 1) vec3_print(ray.direction), vec3_print(ray.origin);
            if (i == BUFFER_W/2 && j == BUFFER_H/2) vec3_print(ray.direction), vec3_print(ray.origin);
            if (i == BUFFER_W-1 && j == BUFFER_H -1) vec3_print(ray.direction), vec3_print(ray.origin);
                
            // get color for every ray
            Color3 r_color = calc_ray_color(ray);
            
            // j as row, i as column multipled by buffer to select the row
            image_buffer[j*(int)BUFFER_W+(int)i] = set_ray_color(r_color);
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
