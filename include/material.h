#ifndef MATERIAL_H
#define MATERIAL_H

#include <stdbool.h>

#include "ray.h"

typedef enum MaterialType {
    MATERIAL_DIFFUSE,
    MATERIAL_METAL
} MaterialType;

typedef struct RTMaterial {
    MaterialType type;
    Color3 albedo;
    float fuzz;
} RTMaterial;

bool material_scatter(const RTMaterial *material, CRay incoming, Point3 hit_point,
                      Vec3 normal, CRay *scattered, Color3 *attenuation);

static inline RTMaterial material_diffuse(Color3 albedo) {
    return (RTMaterial){.type = MATERIAL_DIFFUSE, .albedo = albedo, .fuzz = 0.0f};
}

static inline RTMaterial material_metal(Color3 albedo, float fuzz) {
    if (fuzz < 0.0f) fuzz = 0.0f;
    if (fuzz > 1.0f) fuzz = 1.0f;
    return (RTMaterial){.type = MATERIAL_METAL, .albedo = albedo, .fuzz = fuzz};
}

#endif
