#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdbool.h>

#include "ray.h"

typedef enum MaterialType {
    MATERIAL_DIFFUSE,
    MATERIAL_METAL,
    MATERIAL_DIELECTRIC
} MaterialType;

typedef struct RTMaterial {
    MaterialType type;
    Color3 albedo;
    float fuzz;
    float refraction_index;
} RTMaterial;

bool material_scatter(const RTMaterial *material, CRay incoming, Point3 hit_point,
                      Vec3 normal, bool front_face, CRay *scattered, Color3 *attenuation);

static inline RTMaterial material_diffuse(Color3 albedo) {
    return (RTMaterial){.type = MATERIAL_DIFFUSE, .albedo = albedo, .fuzz = 0.0f, .refraction_index = 1.0f};
}

static inline RTMaterial material_metal(Color3 albedo, float fuzz) {
    if (fuzz < 0.0f) fuzz = 0.0f;
    if (fuzz > 1.0f) fuzz = 1.0f;
    return (RTMaterial){.type = MATERIAL_METAL, .albedo = albedo, .fuzz = fuzz, .refraction_index = 1.0f};
}

static inline RTMaterial material_dielectric(float refraction_index) {
    return (RTMaterial){
        .type = MATERIAL_DIELECTRIC,
        .albedo = (Color3){1.0f, 1.0f, 1.0f},
        .fuzz = 0.0f,
        .refraction_index = refraction_index
    };
}

#endif
