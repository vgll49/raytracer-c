#ifndef HITTABLE_H
#define HITTABLE_H

#include <stdbool.h>

#include "sphere.h"
#include "material.h"

typedef enum HittableType {
    HITTABLE_SPHERE
} HittableType;

typedef struct HitRecord {
    Point3 point;
    Vec3 normal;       // Always points against the incoming ray.
    float t;
    bool front_face;
    RTMaterial material;
} HitRecord;

typedef struct Hittable {
    HittableType type;
    union {
        Sphere sphere;
    } shape;
    RTMaterial material;
} Hittable;

typedef struct HittableList {
    Hittable *objects;
    unsigned int count;
    unsigned int capacity;
} HittableList;

void hittable_set_face_normal(HitRecord *record, CRay ray, Vec3 outward_normal);
bool hittable_hit(const Hittable *object, CRay ray, float t_min, float t_max, HitRecord *record);
void hittable_list_init(HittableList *list);
bool hittable_list_add(HittableList *list, Hittable object);
bool hittable_list_hit(const HittableList *list, CRay ray, float t_min, float t_max, HitRecord *record);
void hittable_list_destroy(HittableList *list);

static inline Hittable hittable_sphere(Sphere sphere, RTMaterial material) {
    Hittable object = {
        .type = HITTABLE_SPHERE,
        .shape.sphere = sphere,
        .material = material
    };
    return object;
}

#endif
